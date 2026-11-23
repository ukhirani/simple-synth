#pragma once

#include <JuceHeader.h>
#include "Theme.h"

namespace ui
{
    //==========================================================================
    // Value formatters used for knob readouts.
    namespace fmt
    {
        using Formatter = std::function<juce::String (double)>;

        inline juce::String hz (double v)
        {
            return v >= 1000.0 ? juce::String (v / 1000.0, v >= 10000.0 ? 1 : 2) + " kHz"
                               : juce::String (juce::roundToInt (v)) + " Hz";
        }

        inline juce::String ms (double v)
        {
            if (v >= 1000.0) return juce::String (v / 1000.0, 2) + " s";
            if (v < 10.0)    return juce::String (v, 1) + " ms";
            return juce::String (juce::roundToInt (v)) + " ms";
        }

        inline juce::String percent (double v)  { return juce::String (juce::roundToInt (v * 100.0)) + "%"; }

        inline juce::String gainDb (double gain)
        {
            const auto db = juce::Decibels::gainToDecibels (gain, -60.0);
            return (db > 0.05 ? "+" : "") + juce::String (db, 1) + " dB";
        }

        inline Formatter number (int decimals, juce::String suffix = {})
        {
            return [decimals, suffix] (double v)
            {
                return juce::String (v, decimals) + (suffix.isEmpty() ? juce::String() : " " + suffix);
            };
        }
    }

    //==========================================================================
    // Rotary knob bound to an APVTS parameter: caption above, readout below.
    class Knob : public juce::Component
    {
    public:
        Knob (juce::AudioProcessorValueTreeState& state, const juce::String& paramId,
              const juce::String& caption, fmt::Formatter formatter)
            : name (caption.toUpperCase()), format (std::move (formatter))
        {
            slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
            slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
            slider.setRotaryParameters (juce::degreesToRadians (225.0f), juce::degreesToRadians (495.0f), true);
            slider.setMouseDragSensitivity (220);
            slider.setVelocityBasedMode (false);
            slider.setPopupDisplayEnabled (false, false, nullptr);
            addAndMakeVisible (slider);

            attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (state, paramId, slider);

            if (auto* param = state.getParameter (paramId))
            {
                slider.setDoubleClickReturnValue (true, param->convertFrom0to1 (param->getDefaultValue()));
                slider.setTooltip (param->getName (64) + "  (double-click to reset)");
            }

            slider.onValueChange = [this] { repaint (valueArea); };
        }

        void paint (juce::Graphics& g) override
        {
            using namespace colour;
            const bool hot = slider.isMouseOverOrDragging();

            g.setFont (caption (10.0f, true));
            g.setColour (hot ? text : textDim);
            g.drawText (name, captionArea, juce::Justification::centred, false);

            g.setFont (mono (10.5f));
            g.setColour (hot ? text : textDim);
            g.drawText (format ? format (slider.getValue()) : juce::String (slider.getValue(), 2),
                        valueArea, juce::Justification::centred, false);
        }

        void resized() override
        {
            auto r = getLocalBounds();
            captionArea = r.removeFromTop (size::knobLabelH);
            valueArea   = r.removeFromBottom (size::knobValueH);
            const int d = juce::jmin (r.getWidth(), r.getHeight());
            slider.setBounds (r.withSizeKeepingCentre (d, d));
        }

        void mouseEnter (const juce::MouseEvent&) override { repaint(); }
        void mouseExit (const juce::MouseEvent&) override  { repaint(); }

        juce::Slider& getSlider() { return slider; }

    private:
        juce::String name;
        fmt::Formatter format;
        juce::Slider slider;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
        juce::Rectangle<int> captionArea, valueArea;
    };

    //==========================================================================
    // [-] value [+] stepper for integer parameters (octave, semitone).
    class Stepper : public juce::Component
    {
    public:
        Stepper (juce::AudioProcessorValueTreeState& state, const juce::String& paramId, const juce::String& caption)
            : name (caption.toUpperCase())
        {
            // Hidden slider carries the attachment and the parameter range.
            slider.setSliderStyle (juce::Slider::LinearHorizontal);
            addChildComponent (slider);
            attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (state, paramId, slider);

            for (auto* b : { &down, &up })
            {
                addAndMakeVisible (*b);
                b->setMouseCursor (juce::MouseCursor::PointingHandCursor);
            }

            down.setButtonText ("-");
            up.setButtonText ("+");
            down.onClick = [this] { step (-1); };
            up.onClick   = [this] { step (+1); };
            slider.onValueChange = [this] { repaint(); };
        }

        void paint (juce::Graphics& g) override
        {
            using namespace colour;
            g.setFont (caption (10.0f, true));
            g.setColour (textDim);
            g.drawText (name, captionArea, juce::Justification::centredLeft, false);

            g.setColour (well);
            g.fillRect (valueArea);
            g.setColour (borderHi);
            g.drawRect (valueArea.expanded (1, 0), 1);

            const auto v = juce::roundToInt (slider.getValue());
            g.setColour (text);
            g.setFont (mono (12.0f, true));
            g.drawText ((v > 0 ? "+" : "") + juce::String (v), valueArea, juce::Justification::centred, false);
        }

        void resized() override
        {
            auto r = getLocalBounds();
            captionArea = r.removeFromTop (size::knobLabelH);
            r.removeFromTop (2);
            const int bw = r.getHeight();
            down.setBounds (r.removeFromLeft (bw));
            up.setBounds (r.removeFromRight (bw));
            valueArea = r;
        }

    private:
        void step (int delta)
        {
            const auto range = slider.getRange();
            slider.setValue (juce::jlimit (range.getStart(), range.getEnd(), slider.getValue() + delta),
                             juce::sendNotificationSync);
        }

        juce::String name;
        juce::Slider slider;
        juce::TextButton down, up;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
        juce::Rectangle<int> captionArea, valueArea;
    };

    //==========================================================================
    // Segmented control for a choice parameter.
    class Segmented : public juce::Component
    {
    public:
        Segmented (juce::AudioProcessorValueTreeState& state, const juce::String& paramId,
                   const juce::String& caption, const juce::StringArray& labels)
            : name (caption.toUpperCase())
        {
            auto* param = state.getParameter (paramId);
            jassert (param != nullptr);

            for (int i = 0; i < labels.size(); ++i)
            {
                auto* b = buttons.add (new juce::TextButton (labels[i]));
                b->setClickingTogglesState (false);
                b->setMouseCursor (juce::MouseCursor::PointingHandCursor);
                b->onClick = [this, i] { attachment->setValueAsCompleteGesture ((float) i); };
                addAndMakeVisible (b);
            }

            attachment = std::make_unique<juce::ParameterAttachment> (*param, [this] (float v)
            {
                const int idx = juce::roundToInt (v);
                for (int i = 0; i < buttons.size(); ++i)
                    buttons[i]->setToggleState (i == idx, juce::dontSendNotification);
            });
            attachment->sendInitialUpdate();
        }

        void paint (juce::Graphics& g) override
        {
            g.setFont (caption (10.0f, true));
            g.setColour (colour::textDim);
            g.drawText (name, getLocalBounds().removeFromTop (size::knobLabelH), juce::Justification::centredLeft, false);
        }

        void resized() override
        {
            auto r = getLocalBounds();
            r.removeFromTop (size::knobLabelH + 2);
            const int n = buttons.size();
            const int w = r.getWidth();
            for (int i = 0; i < n; ++i)
            {
                const int x0 = r.getX() + w * i / n;
                const int x1 = r.getX() + w * (i + 1) / n;
                // Overlap borders by 1px so segments share an edge.
                buttons[i]->setBounds (x0, r.getY(), x1 - x0 + (i < n - 1 ? 1 : 0), r.getHeight());
            }
        }

    private:
        juce::String name;
        juce::OwnedArray<juce::TextButton> buttons;
        std::unique_ptr<juce::ParameterAttachment> attachment;
    };

    //==========================================================================
    // Module frame: square panel with a numbered header strip.
    class ModulePanel : public juce::Component
    {
    public:
        ModulePanel (int index, juce::String title)
            : number (juce::String (index).paddedLeft ('0', 2)), heading (title.toUpperCase()) {}

        void paint (juce::Graphics& g) override
        {
            using namespace colour;
            auto r = getLocalBounds();

            g.setColour (surface);
            g.fillRect (r);

            auto header = r.removeFromTop (size::headerH);
            g.setColour (raised);
            g.fillRect (header);
            g.setColour (border);
            g.fillRect (header.removeFromBottom (1));

            auto text = getLocalBounds().removeFromTop (size::headerH).reduced (space::s3, 0);
            g.setFont (caption (10.5f, true));
            g.setColour (textMuted);
            g.drawText (number, text.removeFromLeft (22), juce::Justification::centredLeft, false);
            g.setColour (colour::text);
            g.drawText (heading, text, juce::Justification::centredLeft, false);

            // Corner registration mark, top-right.
            const auto hr = getLocalBounds().removeFromTop (size::headerH);
            g.setColour (textMuted);
            g.fillRect (hr.getRight() - space::s3 - 6, hr.getCentreY() - 3, 6, 6);

            g.setColour (borderHi);
            g.drawRect (getLocalBounds(), size::border);
        }

        juce::Rectangle<int> getContentBounds() const
        {
            return getLocalBounds().withTrimmedTop (size::headerH).reduced (space::s3, space::s3);
        }

        // Lay a row of components out evenly across the content area.
        template <typename Container>
        void layoutRow (Container& items, juce::Rectangle<int> area)
        {
            const int n = (int) items.size();
            if (n == 0) return;
            const int w = area.getWidth() / n;
            for (int i = 0; i < n; ++i)
                items[(size_t) i]->setBounds (area.getX() + i * w, area.getY(), w, area.getHeight());
        }

    private:
        juce::String number, heading;
    };

    //==========================================================================
    // A module that is just a row of knobs (envelope, filter, effects).
    class KnobModule : public ModulePanel
    {
    public:
        struct Spec { const char* paramId; const char* caption; fmt::Formatter format; };

        KnobModule (juce::AudioProcessorValueTreeState& state, int index, juce::String title,
                    std::initializer_list<Spec> specs)
            : ModulePanel (index, std::move (title))
        {
            for (const auto& s : specs)
                addAndMakeVisible (*knobs.emplace_back (std::make_unique<Knob> (state, s.paramId, s.caption, s.format)));
        }

        void resized() override { layoutRow (knobs, getContentBounds()); }

        int getNumKnobs() const { return (int) knobs.size(); }

    private:
        std::vector<std::unique_ptr<Knob>> knobs;
    };

    //==========================================================================
    // Lock-free mono sample FIFO written by the audio thread, read by the scope.
    class ScopeBuffer
    {
    public:
        static constexpr int size = 2048;

        void push (float sample) noexcept
        {
            const int w = writePos.load (std::memory_order_relaxed);
            data[(size_t) w].store (sample, std::memory_order_relaxed);
            writePos.store ((w + 1) & (size - 1), std::memory_order_release);
        }

        // Copies the most recent `count` samples, oldest first.
        void read (float* dest, int count) const noexcept
        {
            const int w = writePos.load (std::memory_order_acquire);
            for (int i = 0; i < count; ++i)
                dest[i] = data[(size_t) ((w - count + i + size) & (size - 1))].load (std::memory_order_relaxed);
        }

    private:
        std::array<std::atomic<float>, size> data {};
        std::atomic<int> writePos { 0 };
    };

    //==========================================================================
    class Scope : public juce::Component, private juce::Timer
    {
    public:
        explicit Scope (const ScopeBuffer& b) : buffer (b) { startTimerHz (30); }

        void paint (juce::Graphics& g) override
        {
            using namespace colour;
            auto r = getLocalBounds().toFloat();

            g.setColour (well);
            g.fillRect (r);

            // Grid: 8 columns, 4 rows, centre line emphasised.
            g.setColour (hairline);
            for (int i = 1; i < 8; ++i)
                g.fillRect (r.getX() + r.getWidth() * (float) i / 8.0f, r.getY(), 1.0f, r.getHeight());
            for (int i = 1; i < 4; ++i)
                g.fillRect (r.getX(), r.getY() + r.getHeight() * (float) i / 4.0f, r.getWidth(), 1.0f);
            g.setColour (border);
            g.fillRect (r.getX(), r.getCentreY(), r.getWidth(), 1.0f);

            // Trigger on a rising zero crossing so periodic waves stand still.
            int start = 0;
            for (int i = 1; i < numSamples - displaySamples; ++i)
                if (samples[(size_t) i - 1] <= 0.0f && samples[(size_t) i] > 0.0f) { start = i; break; }

            juce::Path p;
            const float midY = r.getCentreY();
            const float amp  = r.getHeight() * 0.45f;
            for (int i = 0; i < displaySamples; ++i)
            {
                const float x = r.getX() + r.getWidth() * (float) i / (float) (displaySamples - 1);
                const float y = midY - juce::jlimit (-1.0f, 1.0f, samples[(size_t) (start + i)]) * amp;
                if (i == 0) p.startNewSubPath (x, y); else p.lineTo (x, y);
            }
            g.setColour (text);
            g.strokePath (p, juce::PathStrokeType (1.25f));

            g.setColour (borderHi);
            g.drawRect (getLocalBounds(), 1);
        }

    private:
        void timerCallback() override
        {
            buffer.read (samples.data(), numSamples);
            repaint();
        }

        static constexpr int numSamples = 1024;
        static constexpr int displaySamples = 512;
        const ScopeBuffer& buffer;
        std::array<float, numSamples> samples {};
    };
}

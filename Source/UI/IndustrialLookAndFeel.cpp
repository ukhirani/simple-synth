#include "IndustrialLookAndFeel.h"

using namespace juce;

IndustrialLookAndFeel::IndustrialLookAndFeel()
{
    using namespace ui::colour;

    setColourScheme ({ body,        // windowBackground
                       surface,     // widgetBackground
                       surface,     // menuBackground
                       borderHi,    // outline
                       text,        // defaultText
                       raised,      // defaultFill
                       onAccent,    // highlightedText
                       accent,      // highlightedFill
                       text });     // menuText

    setColour (ResizableWindow::backgroundColourId, body);
    setColour (DocumentWindow::textColourId, text);

    setColour (Label::textColourId, text);
    setColour (Label::outlineColourId, Colours::transparentBlack);

    setColour (Slider::rotarySliderFillColourId, accent);
    setColour (Slider::rotarySliderOutlineColourId, border);
    setColour (Slider::thumbColourId, text);
    setColour (Slider::textBoxTextColourId, textDim);
    setColour (Slider::textBoxOutlineColourId, Colours::transparentBlack);

    setColour (TextButton::buttonColourId, surface);
    setColour (TextButton::buttonOnColourId, accent);
    setColour (TextButton::textColourOffId, text);
    setColour (TextButton::textColourOnId, onAccent);

    setColour (ComboBox::backgroundColourId, well);
    setColour (ComboBox::textColourId, text);
    setColour (ComboBox::outlineColourId, borderHi);
    setColour (ComboBox::arrowColourId, text);
    setColour (ComboBox::focusedOutlineColourId, text);

    setColour (PopupMenu::backgroundColourId, surface);
    setColour (PopupMenu::textColourId, text);
    setColour (PopupMenu::highlightedBackgroundColourId, accent);
    setColour (PopupMenu::highlightedTextColourId, onAccent);

    setColour (TextEditor::backgroundColourId, well);
    setColour (TextEditor::textColourId, text);
    setColour (TextEditor::outlineColourId, borderHi);
    setColour (TextEditor::focusedOutlineColourId, text);
    setColour (TextEditor::highlightColourId, text.withAlpha (0.25f));
    setColour (CaretComponent::caretColourId, text);

    setColour (ScrollBar::thumbColourId, borderHi);
    setColour (TooltipWindow::backgroundColourId, text);
    setColour (TooltipWindow::textColourId, onAccent);
    setColour (TooltipWindow::outlineColourId, text);

    setColour (AlertWindow::backgroundColourId, surface);
    setColour (AlertWindow::textColourId, text);
    setColour (AlertWindow::outlineColourId, borderHi);

    setDefaultSansSerifTypeface (ui::monoRegular());
}

//==============================================================================
void IndustrialLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                                              float pos, float startAngle, float endAngle, Slider& slider)
{
    using namespace ui::colour;

    const auto bounds  = Rectangle<int> (x, y, width, height).toFloat();
    const auto size    = jmin (bounds.getWidth(), bounds.getHeight());
    const auto centre  = bounds.getCentre();
    const auto outerR  = size * 0.5f - 1.0f;
    const auto arcR    = outerR - 4.0f;
    const auto bodyR   = arcR - 6.0f;
    const auto angle   = startAngle + pos * (endAngle - startAngle);
    const bool hot     = slider.isMouseOverOrDragging() && slider.isEnabled();

    // Tick marks: 11 hard ticks around the travel, like a printed panel scale.
    g.setColour (textMuted);
    for (int i = 0; i <= 10; ++i)
    {
        const auto a  = startAngle + (float) i / 10.0f * (endAngle - startAngle);
        const auto tl = (i == 0 || i == 5 || i == 10) ? 4.0f : 2.0f;
        const auto p1 = centre.getPointOnCircumference (outerR, a);
        const auto p2 = centre.getPointOnCircumference (outerR - tl, a);
        g.drawLine ({ p1, p2 }, 1.0f);
    }

    // Track + value arc with butt caps (no rounded ends).
    const PathStrokeType stroke (2.0f, PathStrokeType::mitered, PathStrokeType::butt);

    Path track;
    track.addCentredArc (centre.x, centre.y, arcR, arcR, 0.0f, startAngle, endAngle, true);
    g.setColour (border);
    g.strokePath (track, stroke);

    if (pos > 0.0f)
    {
        Path value;
        value.addCentredArc (centre.x, centre.y, arcR, arcR, 0.0f, startAngle, angle, true);
        g.setColour (slider.isEnabled() ? accent : textMuted);
        g.strokePath (value, stroke);
    }

    // Body.
    g.setColour (raised);
    g.fillEllipse (Rectangle<float> (bodyR * 2.0f, bodyR * 2.0f).withCentre (centre));
    g.setColour (hot ? text : borderHi);
    g.drawEllipse (Rectangle<float> (bodyR * 2.0f, bodyR * 2.0f).withCentre (centre), 1.0f);

    // Needle: a sharp wedge from the centre to the rim.
    Path needle;
    const auto tip   = centre.getPointOnCircumference (bodyR - 1.0f, angle);
    const auto left  = centre.getPointOnCircumference (2.2f, angle - MathConstants<float>::halfPi);
    const auto right = centre.getPointOnCircumference (2.2f, angle + MathConstants<float>::halfPi);
    needle.startNewSubPath (left);
    needle.lineTo (tip);
    needle.lineTo (right);
    needle.closeSubPath();
    g.setColour (text);
    g.fillPath (needle);
}

//==============================================================================
void IndustrialLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour&,
                                                  bool isMouseOver, bool isDown)
{
    using namespace ui::colour;

    const auto r  = button.getLocalBounds().toFloat();
    const bool on = button.getToggleState();

    Colour fill = on ? accent : surface;
    if (! on && isDown)      fill = raised.brighter (0.15f);
    else if (! on && isMouseOver) fill = raised;

    g.setColour (fill);
    g.fillRect (r);

    g.setColour (on || isMouseOver ? text : borderHi);
    g.drawRect (r, 1.0f);
}

void IndustrialLookAndFeel::drawButtonText (Graphics& g, TextButton& button, bool, bool)
{
    using namespace ui::colour;

    g.setFont (getTextButtonFont (button, button.getHeight()));
    g.setColour (! button.isEnabled() ? textMuted
                                      : button.getToggleState() ? onAccent : text);
    g.drawFittedText (button.getButtonText().toUpperCase(), button.getLocalBounds().reduced (4, 0),
                      Justification::centred, 1);
}

Font IndustrialLookAndFeel::getTextButtonFont (TextButton&, int)
{
    return ui::caption (11.0f, true);
}

//==============================================================================
void IndustrialLookAndFeel::drawComboBox (Graphics& g, int width, int height, bool,
                                          int, int, int, int, ComboBox& box)
{
    using namespace ui::colour;

    const auto r = Rectangle<int> (width, height).toFloat();
    g.setColour (well);
    g.fillRect (r);
    g.setColour (box.hasKeyboardFocus (true) || box.isMouseOver (true) ? text : borderHi);
    g.drawRect (r, 1.0f);

    // Downward pointing solid triangle.
    const auto cx = (float) width - 12.0f;
    const auto cy = (float) height * 0.5f;
    Path arrow;
    arrow.addTriangle (cx - 4.0f, cy - 2.0f, cx + 4.0f, cy - 2.0f, cx, cy + 3.0f);
    g.setColour (box.isEnabled() ? text : textMuted);
    g.fillPath (arrow);
}

void IndustrialLookAndFeel::positionComboBoxText (ComboBox& box, Label& label)
{
    label.setBounds (8, 1, box.getWidth() - 28, box.getHeight() - 2);
    label.setFont (getComboBoxFont (box));
    label.setJustificationType (Justification::centredLeft);
}

Font IndustrialLookAndFeel::getComboBoxFont (ComboBox&)
{
    return ui::mono (12.0f);
}

void IndustrialLookAndFeel::drawPopupMenuBackground (Graphics& g, int width, int height)
{
    g.fillAll (ui::colour::surface);
    g.setColour (ui::colour::borderHi);
    g.drawRect (0, 0, width, height, 1);
}

void IndustrialLookAndFeel::drawPopupMenuItem (Graphics& g, const Rectangle<int>& area,
                                               bool isSeparator, bool isActive, bool isHighlighted,
                                               bool isTicked, bool hasSubMenu, const String& text,
                                               const String& shortcutKeyText, const Drawable* icon,
                                               const Colour* textColour)
{
    using namespace ui::colour;

    if (isSeparator)
    {
        g.setColour (border);
        g.fillRect (area.reduced (6, 0).withHeight (1).withCentre (area.getCentre()));
        return;
    }

    if (isHighlighted && isActive)
    {
        g.setColour (accent);
        g.fillRect (area);
    }

    auto r = area.reduced (10, 0);
    g.setColour (! isActive ? textMuted : isHighlighted ? onAccent : ui::colour::text);
    g.setFont (getPopupMenuFont());

    if (isTicked)
    {
        // Small solid square marks the current choice.
        g.fillRect (Rectangle<int> (5, 5).withCentre ({ r.getX() + 3, r.getCentreY() }));
    }

    r.removeFromLeft (14);
    g.drawFittedText (text, r, Justification::centredLeft, 1);

    if (shortcutKeyText.isNotEmpty())
        g.drawText (shortcutKeyText, r, Justification::centredRight, true);

    ignoreUnused (hasSubMenu, icon, textColour);
}

Font IndustrialLookAndFeel::getPopupMenuFont()
{
    return ui::mono (12.0f);
}

//==============================================================================
Font IndustrialLookAndFeel::getLabelFont (Label& label)
{
    return label.getFont();
}

Typeface::Ptr IndustrialLookAndFeel::getTypefaceForFont (const Font& f)
{
    // Anything that asks for the default sans face gets Plex Mono, bold
    // requests get the SemiBold cut.
    if (f.getTypefaceName() == Font::getDefaultSansSerifFontName())
        return f.isBold() ? ui::monoSemiBold() : ui::monoRegular();

    return LookAndFeel_V4::getTypefaceForFont (f);
}

void IndustrialLookAndFeel::drawDocumentWindowTitleBar (DocumentWindow& window, Graphics& g, int w, int h,
                                                        int titleSpaceX, int titleSpaceW,
                                                        const Image*, bool)
{
    using namespace ui::colour;

    g.fillAll (body);
    g.setColour (border);
    g.fillRect (0, h - 1, w, 1);

    g.setColour (window.isActiveWindow() ? text : textDim);
    g.setFont (ui::caption (11.0f, true));
    g.drawText (window.getName().toUpperCase(), titleSpaceX, 0, titleSpaceW, h, Justification::centred, true);
}

void IndustrialLookAndFeel::fillTextEditorBackground (Graphics& g, int, int, TextEditor&)
{
    g.fillAll (ui::colour::well);
}

void IndustrialLookAndFeel::drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& editor)
{
    g.setColour (editor.hasKeyboardFocus (true) ? ui::colour::text : ui::colour::borderHi);
    g.drawRect (0, 0, width, height, 1);
}

void IndustrialLookAndFeel::drawScrollbar (Graphics& g, ScrollBar&, int x, int y, int width, int height,
                                           bool vertical, int thumbStart, int thumbSize, bool isMouseOver, bool)
{
    const auto thumb = vertical ? Rectangle<int> (x + 2, thumbStart, width - 4, thumbSize)
                                : Rectangle<int> (thumbStart, y + 2, thumbSize, height - 4);
    g.setColour (isMouseOver ? ui::colour::textDim : ui::colour::borderHi);
    g.fillRect (thumb);
}

void IndustrialLookAndFeel::drawTooltip (Graphics& g, const String& text, int width, int height)
{
    g.fillAll (ui::colour::text);
    g.setColour (ui::colour::onAccent);
    g.setFont (ui::mono (11.0f));
    g.drawFittedText (text, Rectangle<int> (width, height).reduced (6, 2), Justification::centredLeft, 3);
}

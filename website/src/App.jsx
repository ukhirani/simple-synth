import {Layout, LayoutContent, LayoutHeader, LayoutFooter} from '@astryxdesign/core/Layout';
import {VStack} from '@astryxdesign/core/VStack';
import {HStack} from '@astryxdesign/core/HStack';
import {Grid} from '@astryxdesign/core/Grid';
import {Card} from '@astryxdesign/core/Card';
import {Text} from '@astryxdesign/core/Text';
import {Heading} from '@astryxdesign/core/Heading';
import {Button} from '@astryxdesign/core/Button';
import {Link} from '@astryxdesign/core/Link';
import {Divider} from '@astryxdesign/core/Divider';
import {Icon} from '@astryxdesign/core/Icon';
import {AspectRatio} from '@astryxdesign/core/AspectRatio';
import {CodeBlock} from '@astryxdesign/core/CodeBlock';
import {TopNav, TopNavHeading, TopNavItem} from '@astryxdesign/core/TopNav';
import {ArrowDownTrayIcon, ArrowUpRightIcon} from '@heroicons/react/20/solid';

import {
  PLATFORMS,
  REPO_URL,
  RELEASES_URL,
  detectPlatform,
  downloadUrl,
  formatBytes,
  useLatestRelease,
} from './release';

const MODULES = [
  {name: 'Oscillator', text: 'Sine, square and saw with octave and semitone offsets, plus a noise source.', params: 'WAVE · OCT · SEMI · LEVEL · NOISE'},
  {name: 'Amp Envelope', text: 'Four-stage ADSR shaping every voice from first click to final tail.', params: 'ATK · DEC · SUS · REL'},
  {name: 'Filter', text: 'Resonant low-pass for carving the tone before it hits the effects.', params: 'CUTOFF · RES'},
  {name: 'Crunch', text: 'Fuzz and drive saturation with tone and low-cut shaping.', params: 'FUZZ · DRIVE · TONE · CUT · OUT'},
  {name: 'Chorus', text: 'Detuned, modulated copies that widen a single voice into a stereo field.', params: 'MIX · DEPTH · DETUNE · WIDTH'},
  {name: 'Reverb', text: 'Room reverb with independent dry/wet and band-limited tail.', params: 'DRY · WET · ROOM · LOW · HIGH · RT20'},
  {name: 'Limiter', text: 'Brick-wall output stage so nothing leaves the synth clipped.', params: 'PRE · CEIL · ATK · HOLD · REL'},
  {name: 'Output', text: 'Triggered oscilloscope and file-based presets you can save, browse and share.', params: 'SCOPE · PRESETS'},
];

const BUILD_STEPS = `git clone ${REPO_URL}.git
cd simple-synth
cmake -B build -DCMAKE_BUILD_TYPE=Release   # fetches JUCE 8 automatically
cmake --build build --config Release --parallel`;

function Index({n}) {
  return (
    <Text type="code" color="secondary">
      {String(n).padStart(2, '0')}
    </Text>
  );
}

function SectionTitle({n, title, children}) {
  return (
    <VStack gap={2}>
      <HStack gap={3} vAlign="center">
        <Index n={n} />
        <Heading level={2}>{title}</Heading>
      </HStack>
      {children ? (
        <Text color="secondary" textWrap="pretty">
          {children}
        </Text>
      ) : null}
    </VStack>
  );
}

function Header() {
  return (
    <LayoutHeader>
      <TopNav
        heading={<TopNavHeading heading="SIMPLESYNTH" headingHref="#top" />}
        startContent={
          <>
            <TopNavItem label="Modules" href="#modules" />
            <TopNavItem label="Download" href="#download" />
            <TopNavItem label="Source" href="#source" />
          </>
        }
        endContent={
          <Button
            label="GitHub"
            variant="ghost"
            size="sm"
            href={REPO_URL}
            endContent={<Icon icon={ArrowUpRightIcon} size="sm" color="inherit" />}
          />
        }
      />
    </LayoutHeader>
  );
}

function Hero({release}) {
  const version = release?.tag ?? 'latest';
  return (
    <VStack gap={8} id="top">
      <VStack gap={4} hAlign="start" maxWidth={760}>
        <Text type="code" color="secondary">
          {`${version.toUpperCase()} / OPEN-SOURCE POLY SYNTH / WIN · MAC · LINUX`}
        </Text>
        <Heading level={1} type="display-1" textWrap="balance">
          Seven modules. One signal path. Nothing else.
        </Heading>
        <Text type="large" color="secondary" textWrap="pretty">
          SimpleSynth is a small, honest polyphonic synthesizer. Run it as a standalone app or load it
          as a VST3 / Audio Unit plugin in your DAW. Free, and open source.
        </Text>
        <HStack gap={3} wrap="wrap">
          <Button
            label="Download"
            variant="primary"
            size="lg"
            href="#download"
            endContent={<Icon icon={ArrowDownTrayIcon} size="sm" color="inherit" />}
          />
          <Button label="View source" variant="secondary" size="lg" href={REPO_URL} />
        </HStack>
      </VStack>
      <Card padding={0}>
        <AspectRatio ratio={922 / 728} fit="contain">
          <img
            src="synth.png"
            alt="The SimpleSynth editor: oscillator, envelope, filter, crunch, chorus, reverb and limiter modules above an output scope, in black and white."
          />
        </AspectRatio>
      </Card>
    </VStack>
  );
}

function Modules() {
  return (
    <VStack gap={6} id="modules">
      <SectionTitle n={1} title="Signal path">
        Every voice runs left to right through the same chain. Each module is one panel with a handful of
        knobs. Double-click any knob to reset it.
      </SectionTitle>
      <Grid columns={{minWidth: 240}} gap={2}>
        {MODULES.map((m, i) => (
          <Card key={m.name} padding={4}>
            <VStack gap={3}>
              <HStack gap={3} vAlign="center">
                <Index n={i + 1} />
                <Text weight="semibold">{m.name.toUpperCase()}</Text>
              </HStack>
              <Text color="secondary" type="supporting" textWrap="pretty">
                {m.text}
              </Text>
              <Text type="code" size="xsm">
                {m.params}
              </Text>
            </VStack>
          </Card>
        ))}
      </Grid>
    </VStack>
  );
}

function Download({release}) {
  const detected = detectPlatform();
  const date = release?.date?.toLocaleDateString(undefined, {year: 'numeric', month: 'short', day: 'numeric'});

  return (
    <VStack gap={6} id="download">
      <SectionTitle n={2} title="Download">
        {release
          ? `${release.tag}, released ${date}. Built automatically for every platform from the main branch.`
          : 'Latest release, built automatically for every platform from the main branch.'}
      </SectionTitle>
      <Grid columns={{minWidth: 260, max: 3}} gap={2}>
        {PLATFORMS.map(p => {
          const asset = release?.assets?.[p.asset];
          const size = formatBytes(asset?.size);
          const isDetected = p.id === detected;
          return (
            <Card key={p.id} padding={5}>
              <VStack gap={5} height="100%" vAlign="between">
                <VStack gap={2}>
                  <HStack hAlign="between" vAlign="center">
                    <Heading level={3}>{p.name}</Heading>
                    {isDetected ? (
                      <Text type="code" size="xsm" color="secondary">
                        THIS DEVICE
                      </Text>
                    ) : null}
                  </HStack>
                  <Text type="supporting" color="secondary">
                    {p.arch}
                  </Text>
                </VStack>
                <VStack gap={1}>
                  {p.contents.map(c => (
                    <Text key={c} type="code" size="xsm">
                      {`— ${c}`}
                    </Text>
                  ))}
                </VStack>
                <VStack gap={2}>
                  <Button
                    label={`Download for ${p.name}`}
                    variant={isDetected ? 'primary' : 'secondary'}
                    href={downloadUrl(p.asset)}
                    endContent={<Icon icon={ArrowDownTrayIcon} size="sm" color="inherit" />}
                  />
                  <Text type="code" size="2xs" color="secondary">
                    {size ? `${p.asset} · ${size}` : p.asset}
                  </Text>
                </VStack>
              </VStack>
            </Card>
          );
        })}
      </Grid>
      <Text type="supporting" color="secondary">
        Unzip and run the standalone app, or copy the plugin into your plugin folder (VST3:{' '}
        <Text type="code" size="xsm">
          ~/.vst3
        </Text>
        ,{' '}
        <Text type="code" size="xsm">
          ~/Library/Audio/Plug-Ins/VST3
        </Text>{' '}
        or{' '}
        <Text type="code" size="xsm">
          C:\Program Files\Common Files\VST3
        </Text>
        ). Builds are unsigned: on macOS, right-click the app and choose Open the first time. All versions are on the{' '}
        <Link href={RELEASES_URL} color="primary" hasUnderline>
          releases page
        </Link>
        .
      </Text>
    </VStack>
  );
}

function Source() {
  return (
    <VStack gap={6} id="source">
      <SectionTitle n={3} title="Build from source">
        C++20, CMake 3.22+ and JUCE 8. On Linux, install the usual JUCE dependencies (ALSA, X11, FreeType)
        first.
      </SectionTitle>
      <CodeBlock code={BUILD_STEPS} language="bash" title="terminal" />
    </VStack>
  );
}

function Footer() {
  return (
    <LayoutFooter>
      <HStack hAlign="between" vAlign="center" wrap="wrap" gap={3} paddingBlock={4}>
        <Text type="code" size="xsm" color="secondary">
          {`© ${new Date().getFullYear()} SYNTH8 · SIMPLESYNTH`}
        </Text>
        <HStack gap={4}>
          <Link href={REPO_URL} color="secondary" type="supporting">
            GitHub
          </Link>
          <Link href={RELEASES_URL} color="secondary" type="supporting">
            Releases
          </Link>
          <Link href={`${REPO_URL}/issues`} color="secondary" type="supporting">
            Issues
          </Link>
        </HStack>
      </HStack>
    </LayoutFooter>
  );
}

export default function App() {
  const release = useLatestRelease();
  return (
    <Layout height="auto" contentWidth={1120} defaultHasDividers header={<Header />} footer={<Footer />}>
      <LayoutContent role="main" padding={6} isScrollable={false}>
        <VStack gap={10} paddingBlock={6}>
          <Hero release={release} />
          <Divider />
          <Modules />
          <Divider />
          <Download release={release} />
          <Divider />
          <Source />
        </VStack>
      </LayoutContent>
    </Layout>
  );
}

import {useEffect, useState} from 'react';

export const REPO = 'ukhirani/simple-synth';
export const REPO_URL = `https://github.com/${REPO}`;
export const RELEASES_URL = `${REPO_URL}/releases`;

// Asset names are fixed by .github/workflows/build.yml, so these links always
// resolve to the newest release even before the API call below returns.
export const PLATFORMS = [
  {
    id: 'windows',
    name: 'Windows',
    arch: 'x64 · Windows 10/11',
    asset: 'SimpleSynth-Windows-x64.zip',
    contents: ['Standalone .exe', 'VST3 plugin'],
  },
  {
    id: 'macos',
    name: 'macOS',
    arch: 'Universal · Apple silicon + Intel · 11+',
    asset: 'SimpleSynth-macOS-Universal.zip',
    contents: ['Standalone .app', 'VST3 plugin', 'Audio Unit'],
  },
  {
    id: 'linux',
    name: 'Linux',
    arch: 'x64 · glibc 2.35+',
    asset: 'SimpleSynth-Linux-x64.tar.gz',
    contents: ['Standalone binary', 'VST3 plugin'],
  },
];

export const downloadUrl = asset => `${RELEASES_URL}/latest/download/${asset}`;

export function detectPlatform() {
  if (typeof navigator === 'undefined') return null;
  const p = (navigator.userAgentData?.platform || navigator.platform || navigator.userAgent || '').toLowerCase();
  if (p.includes('win')) return 'windows';
  if (p.includes('mac')) return 'macos';
  if (p.includes('linux') || p.includes('x11')) return 'linux';
  return null;
}

export function formatBytes(n) {
  if (!n) return null;
  return n >= 1048576 ? `${(n / 1048576).toFixed(1)} MB` : `${Math.round(n / 1024)} KB`;
}

// Latest release metadata (version, date, asset sizes). Null until loaded or
// when the API is unreachable; the page works without it.
export function useLatestRelease() {
  const [release, setRelease] = useState(null);
  useEffect(() => {
    const controller = new AbortController();
    fetch(`https://api.github.com/repos/${REPO}/releases/latest`, {
      signal: controller.signal,
      headers: {Accept: 'application/vnd.github+json'},
    })
      .then(r => (r.ok ? r.json() : null))
      .then(data => {
        if (!data) return;
        const assets = Object.fromEntries((data.assets ?? []).map(a => [a.name, a]));
        setRelease({
          tag: data.tag_name,
          date: data.published_at ? new Date(data.published_at) : null,
          url: data.html_url,
          assets,
        });
      })
      .catch(() => {});
    return () => controller.abort();
  }, []);
  return release;
}

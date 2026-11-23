// The industrial theme. `astryx experimental theme editor` wrote this file once and never changes it again.
// The checked settings live in industrial.settings.json and the generated industrial.settings.ts;
// change them with `astryx experimental theme editor set industrial ...`. Add your own changes below: they win over the settings.
import {defineTheme} from '@astryxdesign/core/theme';
import {industrialSettings} from './industrial.settings';

export const industrialTheme = defineTheme({
  extends: industrialSettings,
  name: 'industrial',
});

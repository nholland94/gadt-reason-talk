// import Prism from 'prismjs/components/prism-core';
// import 'prismjs/components/prism-clike';
// import 'prismjs/components/prism-reason';
// import loadLanguages from 'prismjs/components/index';
// loadLanguages(['clike', 'reason']);
import Prism from 'prismjs';
import 'prism-themes/themes/prism-duotone-dark.css'
import 'prismjs/components/prism-clike'
import 'prismjs/components/prism-reason'
import 'prismjs/components/prism-java'
window.Prism = Prism;
import './main.css'; // eslint-disable-line import/first
import main from './Main.bs.js'; // eslint-disable-line import/first


main();

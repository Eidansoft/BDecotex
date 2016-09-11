import {Component} from 'angular2/core';
import {WecotexFamilies} from './families';

@Component({ 
    selector: 'wecotex-window',
    templateUrl: 'app/view/window.html',
    directives: [WecotexFamilies]
    })

export class WecotexWindow {}

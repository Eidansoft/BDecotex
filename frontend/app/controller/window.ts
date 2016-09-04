import {Component} from 'angular2/core';
import {WecotexFamily} from './family'

@Component({ 
    selector: 'wecotex-window',
    templateUrl: 'app/view/window.html',
    directives: [WecotexFamily]
    })

export class WecotexWindow {}

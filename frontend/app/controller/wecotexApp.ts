import {Component} from 'angular2/core';
import {WecotexMenu} from './menu';
import {WecotexWindow} from './window';


@Component({ 
    selector: 'wecotex-app',
    templateUrl: 'app/view/wecotexApp.html',
    styleUrls: ['app/assets/css/wecotexApp.css'],
    directives: [WecotexMenu, WecotexWindow]
    })

export class WecotexApp {}
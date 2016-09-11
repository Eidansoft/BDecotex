import {Component} from 'angular2/core';
import {WecotexMenu} from './menu';
import {WecotexFamilies} from './families';
import {WecotexFamily} from './family';
import {ROUTER_DIRECTIVES, RouteConfig, Router} from 'angular2/router';


@Component({ 
    selector: 'wecotex-app',
    templateUrl: 'app/view/wecotexApp.html',
    styleUrls: ['app/assets/css/wecotexApp.css'],
    directives: [WecotexMenu,
                 WecotexFamilies,
                 WecotexFamily,
                 ROUTER_DIRECTIVES]
    })

@RouteConfig([
    {path: "/families", name: "Families", component: WecotexFamilies, useAsDefault: true},
    {path: "/family", name: "Family", component: WecotexFamily}
])

export class WecotexApp {}
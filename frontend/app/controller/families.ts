import {Component} from 'angular2/core';
import {WecotexFamily} from './family';
import {ROUTER_DIRECTIVES, RouteConfig, Router} from 'angular2/router';

@Component({ 
    selector: 'wecotex-families',
    templateUrl: 'app/view/families.html',
    directives: [ROUTER_DIRECTIVES]
    })

export class WecotexFamilies {
    private familiesList:Array<WecotexFamily>;
    
    public constructor() {
        let f1 = new WecotexFamily();
        f1.setName("Prueba 1");
        f1.setCode("001");
        f1.setId(1);
        let f2 = new WecotexFamily();
        f2.setName("Prueba 1");
        f2.setCode("001");
        f2.setId(2);
        let f3 = new WecotexFamily();
        f3.setName("Prueba 1");
        f3.setCode("001");
        f3.setId(3);
        this.familiesList = [
            f1, f2, f3
        ];
    }
}

import {Component} from 'angular2/core';

@Component({ 
    selector: 'wecotex-family',
    templateUrl: 'app/view/family.html'
    })

export class WecotexFamily {
    private name:string;
    private code:string;
    
    public constructor(name:string, code:string) {
        this.name = name;
        this.code = code;
    }
}

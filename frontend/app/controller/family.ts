import {Component} from 'angular2/core';

@Component({ 
    selector: 'wecotex-family',
    templateUrl: 'app/view/family.html'
    })

export class WecotexFamily {
    private name: string;
    private code: string;
    private id: number;
    
    public setName(name: string) {
        this.name = name;
    }
    
    public setCode(code: string) {
        this.code = code;
    }
    
    public setId(id: number) {
        this.id = id;
    }
}

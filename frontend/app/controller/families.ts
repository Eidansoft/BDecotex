import {Component} from 'angular2/core';
import {WecotexFamily} from './family';

@Component({ 
    selector: 'wecotex-families',
    templateUrl: 'app/view/families.html'
    })

export class WecotexFamilies {
    private familiesList:Array<WecotexFamily>;
    
    public constructor() {
        this.familiesList = [
            new WecotexFamily("PRueba 1", "1"),
            new WecotexFamily("PRueba 2", "11"),
            new WecotexFamily("PRueba 3", "102"),
        ];
    }
}

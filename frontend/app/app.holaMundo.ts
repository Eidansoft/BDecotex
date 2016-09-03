import {Component} from 'angular2/core';

@Component({ 
    selector: 'hola-mundo',
    templateUrl: 'view/holaMundo.html'
    })

export class HolaMundo {
    private nombre:string;
    
    public constructor(){
        this.nombre = "Alejandro Lorente";
    }
}
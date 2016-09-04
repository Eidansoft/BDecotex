import {Component} from 'angular2/core';

@Component({ 
    selector: 'hola-mundo',
    templateUrl: 'view/holaMundo.html',
    styleUrls: ['../assets/css/holaMundo.css']
    })

export class HolaMundo {
    private nombre: string;
    private mostrarTexto: boolean;
    
    public constructor(){
        this.nombre = "Alejandro Lorente";
        this.mostrarTexto = false;
    }
    
    public onClickBtn1(){
        this.mostrarTexto = !this.mostrarTexto;
    }
}
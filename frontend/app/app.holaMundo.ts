/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import {Component} from 'angular2/core';

@Component({ 
    selector: 'hola-mundo',
    template: '<h1>Hola mundo en Angular2 !!!</h1>\n\
                <p>Bienvenido <strong>{{nombre}}</strong>.\n\
                Por favor, ten en cuenta que esto es una prueba y hay que tomarla como tal.</p>'
    })

export class HolaMundo {
    private nombre:string;
    
    public constructor(){
        this.nombre = "Alejandro Lorente";
    }
}
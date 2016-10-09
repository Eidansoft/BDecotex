/// <reference path="../../typings/angularjs/angular.d.ts" />
class BackendService
{
    private descargasRealizadas;
    
    constructor(){
        this.descargasRealizadas = ["Esta es la", "Prueba con", "Typescript"];
    }

    public nuevaDescarga(descarga): void
    {
        this.descargasRealizadas.push(descarga);
    }
    
    public getDescargas()
    {
        return this.descargasRealizadas;
    }
}

angular.module('bdecotex').factory('BackendService', [() => new BackendService()]);

/// <reference path="../../typings/angularjs/angular.d.ts" />
class BackendService
{
    private descargasRealizadas;
    protected httpService;
    
    constructor($http: ng.IHttpService){
        this.descargasRealizadas = ["Esta es la", "Prueba con", "Typescript"];
        this.httpService = $http;
    }

    public nuevaDescarga(descarga): void
    {
        this.descargasRealizadas.push(descarga);
    }
    
    public getDescargas()
    {
        return this.httpService.get('/bdecotex/backend/app/family');
        //return this.descargasRealizadas;
    }
}

angular.module('bdecotex').service('BackendService', BackendService);
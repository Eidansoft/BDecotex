/// <reference path="../../typings/angularjs/angular.d.ts" />
class BackendService
{
    static dependencies = [];
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
    
    public getDescargas(): ng.IHttpPromise<BackendResponseData>
    {
        return this.httpService.get('/bdecotex/backend/app/family');
    }
}

bdecotexApp.service('BackendService', BackendService);

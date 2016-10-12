/// <reference path="../../typings/angularjs/angular.d.ts" />
class BackendService
{
    static dependencies = ['$http', BackendService];
    protected httpService: ng.IHttpService;
    
    constructor($http: ng.IHttpService){
        this.httpService = $http;
    }

    public nuevaDescarga(descarga): void
    {
        alert("NOT yet implemented");
    }
    
    public getDescargas(): ng.IHttpPromise<BackendResponseData>
    {
        return this.httpService.get('/bdecotex/backend/app/family');
    }
}

bdecotexApp.service('BackendService', BackendService.dependencies);

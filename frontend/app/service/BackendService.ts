/// <reference path="../../typings/angularjs/angular.d.ts" />
class BackendService
{
    static dependencies = ['$http', BackendService];
    protected httpService: ng.IHttpService;
    
    constructor($http: ng.IHttpService){
        this.httpService = $http;
    }
    
    public getFamilies(): ng.IHttpPromise<ModelResponse>
    {
        return this.httpService.get('/bdecotex/backend/app/family');
    }
    
    public addFamily(family: ModelFamily): ng.IHttpPromise<ModelResponse>
    {
        return this.httpService.post('/bdecotex/backend/app/family', family);
    }
}

bdecotexApp.service('BackendService', BackendService.dependencies);

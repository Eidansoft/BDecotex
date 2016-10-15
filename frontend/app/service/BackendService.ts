class BackendService
{
    static dependencies = ['$http', BackendService];
    protected httpService: ng.IHttpService;
    
    constructor($http: ng.IHttpService){
        this.httpService = $http;
    }
    
    public getFamilies(): ng.IHttpPromise<any>
    {
        console.log('GET /bdecotex/backend/app/family');
        return this.httpService.get('/bdecotex/backend/app/family');
    }
    
    public addFamily(family: ModelFamily): ng.IHttpPromise<any>
    {
        console.log('POST /bdecotex/backend/app/family');
        return this.httpService.post('/bdecotex/backend/app/family', family);
    }
    
    public deleteFamily(id_family:number): ng.IHttpPromise<any>{
        console.log('DELETE /bdecotex/backend/app/family');
        return this.httpService.delete('/bdecotex/backend/app/family/' + id_family);
    }
}

bdecotexApp.service('BackendService', BackendService.dependencies);

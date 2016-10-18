class ServiceBackend
{
    static dependencies = ['$http', ServiceBackend];
    private httpHandler: ng.IHttpService;
    private backendPath: string;
    
    constructor($http: ng.IHttpService){
        this.httpHandler = $http;
        this.backendPath = '/bdecotex/backend/app';
    }
    
    private getHttpHandler(requestConf: ng.IRequestConfig): ng.IPromise<any> {
        return this.httpHandler(requestConf);
    }
    
    public createNewFamily(family: ModelFamily): ng.IHttpPromise<any>
    {
        var req = {
            method: 'POST',
            url: this.backendPath + '/family',
            data: family
        }

        return this.getHttpHandler(req);
    }
    
    public getAllFamilies(): ng.IHttpPromise<any>
    {
        var req = {
            method: 'GET',
            url: this.backendPath + '/family'
        }

        return this.getHttpHandler(req);
    }
    
    public updateFamily(family: ModelFamily): ng.IHttpPromise<any>{
        var req = {
            method: 'PUT',
            url: this.backendPath + '/family/' + family.id_family,
            data: family
        }

        return this.getHttpHandler(req);
    }
    
    public deleteFamilyById(id_family:number): ng.IHttpPromise<any>{
        var req = {
            method: 'DELETE',
            url: this.backendPath + '/family/' + id_family
        }

        return this.getHttpHandler(req);
    }
}

bdecotexApp.service('ServiceBackend', ServiceBackend.dependencies);

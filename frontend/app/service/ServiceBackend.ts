class ServiceBackend
{
    static dependencies = ['$http', ServiceBackend];
    private httpHandler: ng.IHttpService;
    private backendPath: string;
    
    constructor($http: ng.IHttpService){
        this.httpHandler = $http;
        this.backendPath = '/bdecotex/backend/app';
    }
    
    public createNewFamily(family: ModelFamily): ng.IHttpPromise<any>
    {
        var req = {
            method: 'POST',
            url: this.backendPath + '/family',
            data: family
        }

        return this.httpHandler(req);
    }
    
    public getAllFamilies(): ng.IHttpPromise<any>
    {
        var req = {
            method: 'GET',
            url: this.backendPath + '/family'
        }

        return this.httpHandler(req);
    }
    
    public updateFamily(family: ModelFamily): ng.IHttpPromise<any>{
        var req = {
            method: 'PUT',
            url: this.backendPath + '/family/' + family.id_family,
            data: family
        }

        return this.httpHandler(req);
    }
    
    public deleteFamilyById(id_family:number): ng.IHttpPromise<any>{
        var req = {
            method: 'DELETE',
            url: this.backendPath + '/family/' + id_family
        }

        return this.httpHandler(req);
    }
}

bdecotexApp.service('ServiceBackend', ServiceBackend.dependencies);

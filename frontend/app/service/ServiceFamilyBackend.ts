class ServiceFamilyBackend extends ServiceBackend
{
    static dependencies = ['$http', 'PubSub', ServiceFamilyBackend];
    private familyPath: string;
    
    constructor($http: ng.IHttpService, pubsub: any){
        super($http, pubsub);
        this.familyPath = "/family";
    }
        
    public createNewFamily(family: ModelFamily, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'POST',
            url: this.backendPath + this.familyPath,
            data: family
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public getFamily(id_family:number, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'GET',
            url: this.backendPath + this.familyPath + '/' + id_family
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public getAllFamilies(onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'GET',
            url: this.backendPath + this.familyPath
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public updateFamily(family: ModelFamily, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'PUT',
            url: this.backendPath + this.familyPath + '/' + family.id_family,
            data: family
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public deleteFamilyById(id_family:number, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'DELETE',
            url: this.backendPath + this.familyPath + '/' + id_family
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
}

bdecotexApp.service('ServiceFamilyBackend', ServiceFamilyBackend.dependencies);

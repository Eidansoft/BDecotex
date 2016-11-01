class ServiceSexBackend extends ServiceBackend
{
    static dependencies = ['$http', 'PubSub', ServiceSexBackend];
    private sexPath: string;
    
    constructor($http: ng.IHttpService, pubsub: any){
        super($http, pubsub);
        this.sexPath = "/sex";
    }
        
    public createNewSex(sex: ModelSex, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'POST',
            url: this.backendPath + this.sexPath,
            data: sex
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public getSex(id_sex:number, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'GET',
            url: this.backendPath + this.sexPath + '/' + id_sex
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public getAllSex(onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'GET',
            url: this.backendPath + this.sexPath
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public updateSex(sex: ModelSex, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'PUT',
            url: this.backendPath + this.sexPath + '/' + sex.id_sex,
            data: sex
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public deleteSexById(id_sex:number, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'DELETE',
            url: this.backendPath + this.sexPath + '/' + id_sex
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
}

bdecotexApp.service('ServiceSexBackend', ServiceSexBackend.dependencies);

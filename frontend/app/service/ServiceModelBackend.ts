class ServiceModelBackend extends ServiceBackend
{
    static dependencies = ['$http', 'PubSub', ServiceModelBackend];
    private modelPath: string;
    
    constructor($http: ng.IHttpService, pubsub: any){
        super($http, pubsub);
        this.modelPath = "/model";
    }
        
    public createNewModel(model: ModelModel, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'POST',
            url: this.backendPath + this.modelPath,
            data: model
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public getAllModel(onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'GET',
            url: this.backendPath + this.modelPath
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public updateModel(model: ModelModel, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'PUT',
            url: this.backendPath + this.modelPath + '/' + model.id_model,
            data: model
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public deleteModelById(id_model:number, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'DELETE',
            url: this.backendPath + this.modelPath + '/' + id_model
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
}

bdecotexApp.service('ServiceModelBackend', ServiceModelBackend.dependencies);

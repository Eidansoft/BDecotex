class ServiceBackend
{
    static dependencies = ['$http', 'PubSub', ServiceBackend];
    private httpHandler: ng.IHttpService;
    private pubsubHandler: any;
    protected backendPath: string;
    
    constructor($http: ng.IHttpService, pubsub: any){
        this.httpHandler = $http;
        this.pubsubHandler = pubsub;
        this.backendPath = '/bdecotex/backend/app';
    }
    
    protected getHttpHandler(requestConf: ng.IRequestConfig, onSuccessResult: Function, onErrorResult?: Function): void {
        this.pubsubHandler.publish('SHOW_WAITING_SCREEN', true);
        this.httpHandler(requestConf).then(
            (successResponse) => {
                onSuccessResult(successResponse.data);
                this.pubsubHandler.publish('HIDE_WAITING_SCREEN', true);
            },
            (errorResponse) => {
                let errorDesc = "ERROR " + errorResponse.status + ": " + errorResponse.statusText;
                if (errorResponse.data.message != undefined){
                    errorDesc += ". Description: " + errorResponse.data.message + " (" + errorResponse.data.code + ")";
                }
                console.log(errorDesc);
                if (onErrorResult != undefined){
                    onErrorResult(errorResponse);
                }
                this.pubsubHandler.publish('HIDE_WAITING_SCREEN', true);
            }
        );
    }
    
    public createNewFamily(family: ModelFamily, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'POST',
            url: this.backendPath + '/family',
            data: family
        }

        this.getHttpHandler(req, onSuccessResult, onErrorResult);
    }
    
    public getAllFamilies(onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'GET',
            url: this.backendPath + '/family'
        }

        this.getHttpHandler(req, onSuccessResult, onErrorResult);
    }
    
    public updateFamily(family: ModelFamily, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'PUT',
            url: this.backendPath + '/family/' + family.id_family,
            data: family
        }

        this.getHttpHandler(req, onSuccessResult, onErrorResult);
    }
    
    public deleteFamilyById(id_family:number, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'DELETE',
            url: this.backendPath + '/family/' + id_family
        }

        this.getHttpHandler(req, onSuccessResult, onErrorResult);
    }
}

bdecotexApp.service('ServiceBackend', ServiceBackend.dependencies);

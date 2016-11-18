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
    
    protected processHttpRequest(requestConf: ng.IRequestConfig, onSuccessResult: Function, onErrorResult?: Function): void {
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
                this.pubsubHandler.publish('SHOW_MESSAGE', new MessageScreen(errorResponse.data.message, 'danger', 'ERROR ('+errorResponse.data.code+'): '));
            }
        );
    }
}

bdecotexApp.service('ServiceBackend', ServiceBackend.dependencies);

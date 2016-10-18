class ServiceBackend
{
    static dependencies = ['$http', 'PubSub', ServiceBackend];
    private httpHandler: ng.IHttpService;
    private pubsubHandler: any;
    private backendPath: string;
    
    constructor($http: ng.IHttpService, pubsub: any){
        this.httpHandler = $http;
        this.pubsubHandler = pubsub;
        this.backendPath = '/bdecotex/backend/app';
    }
    
    private getHttpHandler(requestConf: ng.IRequestConfig, onSuccessResult: Function): void {
        this.pubsubHandler.publish('SHOW_WAITING_SCREEN', true);
        this.httpHandler(requestConf).then(
            (successResponse) => {
                onSuccessResult(successResponse.data);
                this.pubsubHandler.publish('HIDE_WAITING_SCREEN', true);
            },
            (errorResponse) => {
                console.log("ERROR " + errorResponse.data.code + ": " + errorResponse.data.message);
            }
        );
    }
    
    public createNewFamily(family: ModelFamily, onSuccessResult: Function): void
    {
        var req = {
            method: 'POST',
            url: this.backendPath + '/family',
            data: family
        }

        this.getHttpHandler(req, onSuccessResult);
    }
    
    public getAllFamilies(onSuccessResult: Function): void
    {
        var req = {
            method: 'GET',
            url: this.backendPath + '/family'
        }

        this.getHttpHandler(req, onSuccessResult);
    }
    
    public updateFamily(family: ModelFamily, onSuccessResult: Function): void
    {
        var req = {
            method: 'PUT',
            url: this.backendPath + '/family/' + family.id_family,
            data: family
        }

        this.getHttpHandler(req, onSuccessResult);
    }
    
    public deleteFamilyById(id_family:number, onSuccessResult: Function): void
    {
        var req = {
            method: 'DELETE',
            url: this.backendPath + '/family/' + id_family
        }

        this.getHttpHandler(req, onSuccessResult);
    }
}

bdecotexApp.service('ServiceBackend', ServiceBackend.dependencies);

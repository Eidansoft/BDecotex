class ServiceLineBackend extends ServiceBackend
{
    static dependencies = ['$http', 'PubSub', ServiceLineBackend];
    private linePath: string;
    
    constructor($http: ng.IHttpService, pubsub: any){
        super($http, pubsub);
        this.linePath = "/line";
    }
        
    public createNewLine(line: ModelLine, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'POST',
            url: this.backendPath + this.linePath,
            data: line
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public getAllLines(onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'GET',
            url: this.backendPath + this.linePath
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public updateLine(line: ModelLine, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'PUT',
            url: this.backendPath + this.linePath + '/' + line.id_line,
            data: line
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
    
    public deleteLineById(id_line:number, onSuccessResult: Function, onErrorResult?: Function): void
    {
        var req = {
            method: 'DELETE',
            url: this.backendPath + this.linePath + '/' + id_line
        }

        this.processHttpRequest(req, onSuccessResult, onErrorResult);
    }
}

bdecotexApp.service('ServiceLineBackend', ServiceLineBackend.dependencies);

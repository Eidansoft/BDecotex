/// <reference path="../../typings/angularjs/angular.d.ts" />
class BackendResponseData
{
    static dependencies = [BackendResponseData];
    private code: number;
    private messsage: string;
    private httpCode: number;
    
    constructor(){}
    
    public getCode(): number {
        return this.code;
    }
    
    public getMessage(): string {
        return this.messsage;
    }
    
    public getHttpCode(): number {
        return this.httpCode;
    }
}

bdecotexApp.service('BackendResponseData', BackendResponseData.dependencies);
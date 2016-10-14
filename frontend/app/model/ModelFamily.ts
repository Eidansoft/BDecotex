/// <reference path="../../typings/angularjs/angular.d.ts" />
class ModelFamily
{
    protected id_family: number;
    protected description: string;
    protected code: string;
    
    constructor(description:string, code:string, id?:number){
        this.description = description;
        this.code = code;
        if (id != undefined){
            this.id_family = id;
        }
    }
    
    public getIdFamily():number {
        return this.id_family;
    }
    
    public getDescription():string {
        return this.description;
    }
    
    public getCode():string {
        return this.code;
    }
}

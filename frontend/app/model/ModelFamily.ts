class ModelFamily
{
    public id_family: number;
    public description: string;
    public code: string;
    
    constructor(description?:string, code?:string, id?:number){
        if (description != undefined){
            this.description = description;
        }
        
        if (code != undefined){
            this.code = code;
        }
        
        if (id != undefined){
            this.id_family = id;
        }
    }
}

class ModelLine
{
    public id_line: number;
    public name: string;
    public code: string;
    
    constructor(name?:string, code?:string, id?:number){
        if (name != undefined){
            this.name = name;
        }
        
        if (code != undefined){
            this.code = code;
        }
        
        if (id != undefined){
            this.id_line = id;
        }
    }
}

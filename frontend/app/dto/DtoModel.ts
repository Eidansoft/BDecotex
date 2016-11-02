class DtoModel
{
    public id_model: number;
    public xid_family: number;
    public xid_line: number;
    public xid_sex: number;
    public variant: number;
    public identifier: string;
    public description: string;
    public front: string;
    public back: string;
    public neck: string;
    public arm: string;
    public observations: string;
    public model_number_parent: string;
    public xid_model_parent: string;
    public creation_date: string;
    public client: string;
    public old_ref: string;
    
    constructor(idFamily?: number, idLine?:number, idSex?:number, variant?:number){
        if (idFamily != undefined){
            this.xid_family = idFamily;
        }
        
        if (idLine != undefined){
            this.xid_line = idLine;
        }
        
        if (idSex != undefined){
            this.xid_sex = idSex;
        }
        
        if (variant != undefined){
            this.variant = variant;
        }
    }
}

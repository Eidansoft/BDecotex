class ModelModel
{
    public id_model: number;
    public family: ModelFamily;
    public line: ModelLine;
    public sex: ModelSex;
    public variant: number;
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
    
    constructor(dto?: DtoModel){
        if (dto != undefined){
            if (dto.id_model != undefined){
                this.id_model = dto.id_model;
            }
            if (dto.variant != undefined){
                this.variant = dto.variant;
            }
            if (dto.description != undefined){
                this.description = dto.description;
            }
            if (dto.front != undefined){
                this.front = dto.front;
            }
            if (dto.back != undefined){
                this.back = dto.back;
            }
            if (dto.neck != undefined){
                this.neck = dto.neck;
            }
            if (dto.arm != undefined){
                this.arm = dto.arm;
            }
            if (dto.observations != undefined){
                this.observations = dto.observations;
            }
            if (dto.model_number_parent != undefined){
                this.model_number_parent = dto.model_number_parent;
            }
            if (dto.xid_model_parent != undefined){
                this.xid_model_parent = dto.xid_model_parent;
            }
            if (dto.client != undefined){
                this.client = dto.client;
            }
            if (dto.old_ref != undefined){
                this.old_ref = dto.old_ref;
            }
        }
    }
    
    public getDto(): DtoModel{
        let res: DtoModel = (JSON.parse(JSON.stringify(this)));
        res.xid_family = this.family.id_family;
        res.xid_line = this.line.id_line;
        res.xid_sex = this.sex.id_sex;
        return res;
    }
}

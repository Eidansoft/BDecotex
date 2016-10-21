class ControllerSex
{
    static dependencies = ['ServiceSexBackend', ControllerSex];
    private backendHandler: ServiceSexBackend;
    private sexList: Array<ModelSex>;
    private sexSelected: ModelSex;
    
    constructor(serviceBakend: ServiceSexBackend)
    {
        this.backendHandler = serviceBakend;
        
        this.backendHandler.getAllSex((sexArray)=>{
            this.sexList = <Array<ModelSex>>sexArray;
            console.log("Sexos recibidos");
        });
    }

    protected selectSex(sex: ModelSex){
        // Clone the object to edit to avoid modify the original
        this.sexSelected = (JSON.parse(JSON.stringify(sex)));
    }
    
    protected createNewSex(){
        this.sexSelected = new ModelSex();
    }
    
    protected saveSex(){
        if (this.sexSelected.id_sex != undefined){
            this.backendHandler.updateSex(this.sexSelected, ()=>{
                this.sexList = this.sexList.map(sex=>{
                    let res = sex;
                    if (sex.id_sex == this.sexSelected.id_sex){
                        res = this.sexSelected;
                    }
                    return res;
                });
                console.log("Sexo editado");
                this.sexSelected = undefined;
            });
        } else {
            this.backendHandler.createNewSex(this.sexSelected, (createdSex)=>{
                this.sexList.push(<ModelSex>createdSex);
                console.log("Sexo nuevo creado");
                this.sexSelected = undefined;
            });
        }
    }
    
    protected deleteSex(){
        this.backendHandler.deleteSexById(this.sexSelected.id_sex, ()=>{
            this.sexList = this.sexList.filter(sex=>{
                let res = true;
                if (sex.id_sex == this.sexSelected.id_sex){
                    res = false;
                }
                return res;
            });
            console.log("Sexo eliminado");
            this.sexSelected = undefined;
        });
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerSex', ControllerSex.dependencies);

class ControllerFamily
{
    static dependencies = ['ServiceFamilyBackend', ControllerFamily];
    private backendHandler: ServiceFamilyBackend;
    private familyList: Array<ModelFamily>;
    private familySelected: ModelFamily;
    
    constructor(serviceBackend: ServiceFamilyBackend) {
        this.backendHandler = serviceBackend;
        
        this.backendHandler.getAllFamilies((familiesArray)=>{
            this.familyList = <Array<ModelFamily>>familiesArray;
            console.log("Familias recibidas");
        });
    }

    protected selectFamily(family: ModelFamily){
        // Clone the object to edit to avoid modify the original
        this.familySelected = (JSON.parse(JSON.stringify(family)));
    }
    
    protected createNewFamily(){
        this.familySelected = new ModelFamily();
    }
    
    protected saveFamily(){
        if (this.familySelected.id_family != undefined){
            this.backendHandler.updateFamily(this.familySelected, ()=>{
                this.familyList = this.familyList.map(family=>{
                    let res = family;
                    if (family.id_family == this.familySelected.id_family){
                        res = this.familySelected;
                    }
                    return res;
                });
                console.log("Familia editada");
                this.familySelected = undefined;
            });
        } else {
            this.backendHandler.createNewFamily(this.familySelected, (createdFamily)=>{
                this.familyList.push(<ModelFamily>createdFamily);
                console.log("Familia nueva creada");
                this.familySelected = undefined;
            });
        }
    }
    
    protected deleteFamily(){
        this.backendHandler.deleteFamilyById(this.familySelected.id_family, ()=>{
            this.familyList = this.familyList.filter(family=>{
                let res = true;
                if (family.id_family == this.familySelected.id_family){
                    res = false;
                }
                return res;
            });
            console.log("Familia eliminada");
            this.familySelected = undefined;
        });
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerFamily', ControllerFamily.dependencies);

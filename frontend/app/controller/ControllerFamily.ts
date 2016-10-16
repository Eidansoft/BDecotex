class ControllerFamily
{
    static dependencies = ['ServiceBackend', ControllerFamily];
    private backendHandler: ServiceBackend;
    private familyList: Array<ModelFamily>;
    private familySelected: ModelFamily;
    
    constructor(serviceBackend: ServiceBackend) {
        this.backendHandler = serviceBackend;
        
        this.backendHandler.getAllFamilies().then(
            successResponse => {
                this.familyList = <Array<ModelFamily>>successResponse.data;
            },
            errorResponse => {
                console.log("ERROR " + errorResponse.data.code + ": " + errorResponse.data.message);
            }
        );
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
            this.backendHandler.updateFamily(this.familySelected).then(
                successResponse => {
                    this.familyList = this.familyList.map(family=>{
                        let res = family;
                        if (family.id_family == this.familySelected.id_family){
                            res = this.familySelected;
                        }
                        return res;
                    });
                    console.log("Familia salvada")
                },
                errorResponse => {
                    console.log("ERROR " + errorResponse.data.code + ": " + errorResponse.data.message);
                }
            );
        } else {
            this.backendHandler.createNewFamily(this.familySelected).then(
                successResponse => {
                    this.familyList.push(<ModelFamily>successResponse.data);
                    this.familySelected = undefined;
                    console.log("Familia nueva creada")
                },
                errorResponse => {
                    console.log("ERROR " + errorResponse.data.code + ": " + errorResponse.data.message);
                }
            );
        }
    }
    
    protected deleteFamily(){
        this.backendHandler.deleteFamilyById(this.familySelected.id_family).then(
            successResponse => {
                this.familyList = this.familyList.filter(family=>{
                    let res = true;
                    if (family.id_family == this.familySelected.id_family){
                        res = false;
                    }
                    return res;
                });
                console.log("Familia eliminada")
            },
            errorResponse => {
                console.log("ERROR " + errorResponse.data.code + ": " + errorResponse.data.message);
            }
        );
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerFamily', ControllerFamily.dependencies);

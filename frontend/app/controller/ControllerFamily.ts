class ControllerFamily
{
    static dependencies = ['ServiceBackend', 'PubSub', ControllerFamily];
    private backendHandler: ServiceBackend;
    private pubsubHandler: any;
    private familyList: Array<ModelFamily>;
    private familySelected: ModelFamily;
    
    constructor(serviceBackend: ServiceBackend, pubsub: any) {
        this.backendHandler = serviceBackend;
        this.pubsubHandler = pubsub;
        
        this.pubsubHandler.publish('SHOW_WAITING_SCREEN', true);
        this.backendHandler.getAllFamilies().then(
            successResponse => {
                this.familyList = <Array<ModelFamily>>successResponse.data;
                this.pubsubHandler.publish('HIDE_WAITING_SCREEN', true);
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
        this.pubsubHandler.publish('SHOW_WAITING_SCREEN', true);
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
                    this.familySelected = undefined;
                    console.log("Familia salvada");
                    this.pubsubHandler.publish('HIDE_WAITING_SCREEN', true);
                },
                errorResponse => {
                    console.log("ERROR " + errorResponse.data.code + ": " + errorResponse.data.message);
                    this.familySelected = undefined;
                }
            );
        } else {
            this.backendHandler.createNewFamily(this.familySelected).then(
                successResponse => {
                    this.familyList.push(<ModelFamily>successResponse.data);
                    console.log("Familia nueva creada");
                    this.familySelected = undefined;
                    this.pubsubHandler.publish('HIDE_WAITING_SCREEN', true);
                },
                errorResponse => {
                    console.log("ERROR " + errorResponse.data.code + ": " + errorResponse.data.message);
                    this.familySelected = undefined;
                }
            );
        }
    }
    
    protected deleteFamily(){
        this.pubsubHandler.publish('SHOW_WAITING_SCREEN', true);
        this.backendHandler.deleteFamilyById(this.familySelected.id_family).then(
            successResponse => {
                this.familyList = this.familyList.filter(family=>{
                    let res = true;
                    if (family.id_family == this.familySelected.id_family){
                        res = false;
                    }
                    return res;
                });
                console.log("Familia eliminada");
                this.familySelected = undefined;
                this.pubsubHandler.publish('HIDE_WAITING_SCREEN', true);
            },
            errorResponse => {
                console.log("ERROR " + errorResponse.data.code + ": " + errorResponse.data.message);
                this.familySelected = undefined;
            }
        );
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerFamily', ControllerFamily.dependencies);

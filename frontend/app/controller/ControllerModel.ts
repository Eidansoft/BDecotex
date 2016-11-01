class ControllerModel
{
    static dependencies = ['ServiceModelBackend', ControllerModel];
    private backendHandler: ServiceModelBackend;
    private modelList: Array<ModelModel>;
    private modelSelected: ModelModel;
    private gridOptions: any;
    private gridApi: uiGrid.IGridApi;
    
    constructor(serviceBakend: ServiceModelBackend)
    {
        this.backendHandler = serviceBakend;
        
        this.gridOptions = {
            columnDefs: [
                { field: 'id_model', displayName: 'Codigo', width: 100 },
                { field: 'description', displayName: 'Descripcion' }],
            enableRowSelection: true,
            multiSelect: false,
            enableRowHeaderSelection: false, //not checkbox
            onRegisterApi: (api: uiGrid.IGridApi) => {
                this.gridApi = api;
            }
        }
        
        this.backendHandler.getAllModel((modelArray)=>{
            this.modelList = <Array<ModelModel>>modelArray;
            this.gridOptions.data = this.modelList;
            console.log("Modelos recibidos");
        });
    }

    protected editModel() {
        let selections = this.gridApi.selection.getSelectedGridRows();
        if (selections.length === 1){
            this.selectModel(selections[0].entity);
        } else {
            alert("Por favor selecciona un modelo");
        }
    }
    
    protected selectModel(model: ModelModel){
        // Clone the object to edit to avoid modify the original
        this.modelSelected = (JSON.parse(JSON.stringify(model)));
    }
    
    protected createNewModel(){
        this.modelSelected = new ModelModel();
    }
    
    protected saveModel(){
        if (this.modelSelected.id_model != undefined){
            this.backendHandler.updateModel(this.modelSelected, ()=>{
                this.modelList = this.modelList.map(model=>{
                    let res = model;
                    if (model.id_model == this.modelSelected.id_model){
                        res = this.modelSelected;
                    }
                    return res;
                });
                console.log("Modelo editado");
                this.modelSelected = undefined;
            });
        } else {
            this.backendHandler.createNewModel(this.modelSelected, (createdModel)=>{
                this.modelList.push(<ModelModel>createdModel);
                console.log("Modelo nuevo creado");
                this.modelSelected = undefined;
            });
        }
    }
    
    protected deleteModel(){
        this.backendHandler.deleteModelById(this.modelSelected.id_model, ()=>{
            this.modelList = this.modelList.filter(model=>{
                let res = true;
                if (model.id_model == this.modelSelected.id_model){
                    res = false;
                }
                return res;
            });
            this.gridOptions.data = this.modelList;
            console.log("Modelo eliminado");
            this.modelSelected = undefined;
        });
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerModel', ControllerModel.dependencies);

class ControllerModel
{
    static dependencies = ['ServiceModelBackend',
                           'ServiceFamilyBackend',
                           'ServiceLineBackend',
                           'ServiceSexBackend',
                           ControllerModel];
    private modelHandler: ServiceModelBackend;
    private familyHandler: ServiceFamilyBackend;
    private lineHandler: ServiceLineBackend;
    private sexHandler: ServiceSexBackend;
    private modelList: Array<DtoModel>;
    private familyList: Array<ModelFamily>;
    private lineList: Array<ModelLine>;
    private sexList: Array<ModelSex>;
    private modelSelected: ModelModel;
    private gridOptions: uiGrid.IGridOptions;
    private gridApi: uiGrid.IGridApi;
    
    constructor(modelBackend: ServiceModelBackend,
                familyBackend: ServiceFamilyBackend,
                lineBackend: ServiceLineBackend,
                sexBackend: ServiceSexBackend)
    {
        this.modelHandler = modelBackend;
        this.familyHandler = familyBackend;
        this.lineHandler = lineBackend;
        this.sexHandler = sexBackend;
        
        this.gridOptions = {
            columnDefs: [
                { field: 'code', displayName: 'Codigo', width: 100 },
                { field: 'description', displayName: 'Descripcion' }],
            enableRowSelection: true,
            multiSelect: false,
            enableRowHeaderSelection: false, //not checkbox
            onRegisterApi: (api: uiGrid.IGridApi) => {
                this.gridApi = api;
            }
        }
        
        this.modelHandler.getAllModel((modelArray: Array<DtoModel>)=>{
            this.modelList = modelArray;
            this.gridOptions.data = this.modelList;
            console.log("Modelos recibidos");
        });
        
        this.familyHandler.getAllFamilies((familiesArray: Array<ModelFamily>)=>{
            this.familyList = familiesArray;
        });
        
        this.lineHandler.getAllLines((linesArray: Array<ModelLine>)=>{
            this.lineList = linesArray;
        });
        
        this.sexHandler.getAllSex((sexArray: Array<ModelSex>)=>{
            this.sexList = sexArray;
        });
    }

    protected editModel() {
        let selections = this.gridApi.selection.getSelectedGridRows();
        if (selections.length === 1){
            let dto2edit: DtoModel = selections[0].entity;
            this.modelHandler.getModelById(dto2edit.id_model, (model: DtoModel)=>{
                this.modelSelected = this.getModelModel(model);
                console.log("Modelo recibido");
            });
        } else {
            alert("Por favor selecciona un modelo");
        }
    }
    
    protected getModelModel(model: DtoModel): ModelModel{
        // Clone the object to edit in order to avoid modify the original at the view
        let res: ModelModel = new ModelModel(model);
        //fulfill family
        this.familyHandler.getFamily(model.xid_family, (family: ModelFamily)=>{
            res.family = family;
        });
        //fulfill line
        this.lineHandler.getLine(model.xid_line, (line: ModelLine)=>{
            res.line = line;
        });
        //fulfill sex
        this.sexHandler.getSex(model.xid_sex, (sex: ModelSex)=>{
            res.sex = sex;
        });
        return res;
    }
    
    protected createNewModel(){
        this.modelSelected = new ModelModel();
    }
    
    protected saveModel(){
        if (this.modelSelected.id_model != undefined){
            this.modelHandler.updateModel(this.modelSelected, ()=>{
                window.location.reload();
            });
        } else {
            this.modelHandler.createNewModel(this.modelSelected, (createdModel: DtoModel)=>{
                window.location.reload();
            });
        }
    }
    
    protected deleteModel(){
        this.modelHandler.deleteModelById(this.modelSelected.id_model, ()=>{
                window.location.reload();
        });
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerModel', ControllerModel.dependencies);

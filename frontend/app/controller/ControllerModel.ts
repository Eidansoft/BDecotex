class ControllerModel
{
    static dependencies = ['ServiceModelBackend',
                           'ServiceFamilyBackend',
                           'ServiceLineBackend',
                           'ServiceSexBackend',
                           '$scope',
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
    private modelSelectedCopy2VariantChanges: ModelModel;
    private gridOptions: uiGrid.IGridOptions;
    private gridApi: uiGrid.IGridApi;
    
    constructor(modelBackend: ServiceModelBackend,
                familyBackend: ServiceFamilyBackend,
                lineBackend: ServiceLineBackend,
                sexBackend: ServiceSexBackend,
                scope: ng.IScope)
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
        
        scope.$watch(
            () => {return (this.modelSelected !== undefined ? this.modelSelected.family : false);}, 
            (newValue, oldValue) => {
                if (newValue !== oldValue) {
                    this.getVariant();
                }
            }
        );
        scope.$watch(
            () => { return (this.modelSelected !== undefined ? this.modelSelected.line : false);}, 
            (newValue, oldValue) => {
                if (newValue !== oldValue) {
                    this.getVariant();
                }
            }
        );
        scope.$watch(
            () => {return (this.modelSelected !== undefined ? this.modelSelected.sex : false);}, 
            (newValue, oldValue) => {
                if (newValue !== oldValue) {
                    this.getVariant();
                }
            }
        );
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
    
    protected getVariant(){
        if (this.modelSelected !== undefined){
            if (this.modelSelected.family !== undefined
                && this.modelSelected.line !== undefined
                && this.modelSelected.sex !== undefined){
                // if id_model is undefined means we are creating a new model
                if (this.modelSelected.id_model == undefined){
                    this.modelSelected.variant = 0;
                    this.modelHandler.getFreeModelVariants(this.modelSelected, (arrayFreeVariants: Array<any>)=>{
                        this.modelSelected.variant = arrayFreeVariants[0].num;
                    });
                } else {
                    //if not, means we are editing a model so I need to know if
                    // there is a change on family, line or sex
                    if (this.modelSelectedCopy2VariantChanges == undefined){
                        //The first time we save the original values
                        this.modelSelectedCopy2VariantChanges = JSON.parse(JSON.stringify(this.modelSelected));
                    } else {
                        // the rest of times we check if something has changed
                        if (this.modelSelected.family.id_family != this.modelSelectedCopy2VariantChanges.family.id_family
                            || this.modelSelected.line.id_line != this.modelSelectedCopy2VariantChanges.line.id_line
                            || this.modelSelected.sex.id_sex != this.modelSelectedCopy2VariantChanges.sex.id_sex){
                            this.modelHandler.getFreeModelVariants(this.modelSelected, (arrayFreeVariants: Array<any>)=>{
                                this.modelSelected.variant = arrayFreeVariants[0].num;
                            });
                        } else {
                            this.modelSelected.variant = this.modelSelectedCopy2VariantChanges.variant;
                        }
                    }
                }
            }
        }
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerModel', ControllerModel.dependencies);

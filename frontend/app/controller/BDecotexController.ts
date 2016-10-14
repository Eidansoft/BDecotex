/// <reference path="../../typings/angularjs/angular.d.ts" />
class BDecotexController
{
    static dependencies = ['BackendService', BDecotexController];
    private backendHandler;
    public txt:string;
    public nombres;

    constructor(BackendService)
    {
        this.backendHandler = BackendService;
        this.updateFamilyList();
    }

    public add()
    {
        this.backendHandler.addFamily(new ModelFamily(this.txt, this.txt));
        this.updateFamilyList();
    };
    
    private updateFamilyList(){
        this.backendHandler.getFamilies().then(
            result => {
                //console.log(result);
                this.nombres = result.data;
            },
            result => {
                console.log(result);
            }
        );
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'BDecotexController', BDecotexController.dependencies);

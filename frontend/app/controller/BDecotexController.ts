/// <reference path="../../typings/angularjs/angular.d.ts" />
class BDecotexController
{
    static dependencies = ['BackendService', BDecotexController];
    private backendHandler;
    public nombres;

    constructor(BackendService)
    {
        this.backendHandler = BackendService;
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

    public add(nombre)
    {
        this.backendHandler.nuevaDescarga(nombre);
    }; 
}

// Register the controller with Angular
bdecotexApp.controller(
	'BDecotexController', BDecotexController.dependencies);

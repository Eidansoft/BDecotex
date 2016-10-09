/// <reference path="../../typings/angularjs/angular.d.ts" />
class BDecotexController
{
    static dependencies = ['BackendService', BDecotexController];
    private backendApi;
    public name;
    public nombres;

    constructor(BackendService)
    {
        this.backendApi = BackendService;
        this.name = "Nombre de prueba";
        this.nombres = BackendService.getDescargas();
    }

    public add(nombre)
    {
        this.backendApi.nuevaDescarga(nombre);
    }; 
}

// Register the controller with Angular
angular.module('bdecotex', []).controller(
	'BDecotexController', BDecotexController.dependencies);

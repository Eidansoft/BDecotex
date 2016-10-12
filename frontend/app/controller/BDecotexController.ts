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
        BackendService.getDescargas().then(
            result => {
                //console.log(result);
                this.nombres = result.data;
            },
            result => {
                console.log(result);
                alert("Error code: " + result.data.code + ": " + result.data.message + " (HTTP response " + result.data.httpCode + ")")
            }
        );
    }

    public add(nombre)
    {
        this.backendApi.nuevaDescarga(nombre);
    }; 
}

// Register the controller with Angular
angular.module('bdecotex', []).controller(
	'BDecotexController', BDecotexController.dependencies);

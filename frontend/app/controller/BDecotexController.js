angular.module('bdecotex', [])
    .controller("BDecotexController", ["backendApi", function(backendApi){
        this.name = "Nombre de prueba";
        this.nombres = backendApi.getDescargas();
        this.add = function(nombre){
            backendApi.nuevaDescarga(nombre);
        };
    }])
    .factory("backendApi", function(){
        var descargasRealizadas = ["Manual de Javascript", "Manual de jQuery", "Manual de AngularJS"];

        var interfaz = {
            nombre: "Manolo",
            getDescargas: function(){
                return descargasRealizadas;
            },
            nuevaDescarga: function(descarga){
                descargasRealizadas.push(descarga);
            }
        }
        return interfaz;
    });

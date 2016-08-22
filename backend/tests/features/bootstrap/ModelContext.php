<?php
require_once (dirname(__FILE__).'/CommonContextFunctions.php');
require_once (dirname(__FILE__).'/FamilyContext.php');
require_once (dirname(__FILE__).'/LineContext.php');
require_once (dirname(__FILE__).'/SexContext.php');
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');

use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the Model context.
 */
class ModelContext extends CommonContextFunctions implements Context, SnippetAcceptingContext
{
    private $familyContext;
    private $lineContext;
    private $sexContext;
    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct()
    {
        $this->familyContext = new FamilyContext();
        $this->lineContext = new LineContext();
        $this->sexContext = new SexContext();
    }
 
    /**
     * @Given que el sistema contiene los sexos:
     */
    public function queElSistemaContieneLosSexos(TableNode $table)
    {
        $this->queLaTablaEstaVacia("sex");
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->sexContext->elUsuarioCreaElSexoConCodigo($row['SEXO'], $row['COD']);
        }
    }

    /**
     * @Given que el sistema contiene las lineas:
     */
    public function queElSistemaContieneLasLineas(TableNode $table)
    {
        $this->queLaTablaEstaVacia("line");
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->lineContext->elUsuarioCreaLaLineaConCodigo($row['LINEA'], $row['COD']);
        }
    }

    /**
     * @Given que el sistema contiene las familias:
     */
    public function queElSistemaContieneLasFamilias(TableNode $table)
    {
        $this->queLaTablaEstaVacia("family");
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->familyContext->elUsuarioCreaLaFamiliaConCodigo($row['FAMILIA'], $row['COD']);
        }
    }

    /**
     * @When el usuario crea un modelo de la familia :arg1, linea :arg2, sexo :arg3 y variante :arg4
     */
    public function elUsuarioCreaUnModeloDeLaFamiliaLineaSexoYVariante($arg1, $arg2, $arg3, $arg4)
    {
        if ($arg1 == "null"){
            $family = $arg1;
        } else {
            $this->familyContext->elUsuarioSolicitaElListadoDeTodasLasFamilias();
            $family = $this->familyContext->findFamilyIntoJsonResponse($arg1);
        }
        
        if ($arg2 == "null"){
            $line = $arg2;
        } else {
            $this->lineContext->elUsuarioSolicitaElListadoDeTodasLasLineas();
            $line = $this->lineContext->findFamilyIntoJsonResponse($arg2);
        }
        
        if ($arg3 == "null"){
            $sex = $arg3;
        } else {
            $this->sexContext->elUsuarioSolicitaElListadoDeTodosLosSexos();
            $sex = $this->sexContext->findSexIntoJsonResponse($arg3);
        }
        
        $variante = $arg4;
        
        if($family && $line && $sex){
            $method = UrlApi::URL_METHOD_POST;
            $url = "http://localhost/bdecotex/model";
            $modelData = ["family"  => ($family=="null" ? "" : $family),
                          "line"    => ($line=="null" ? "" : $line),
                          "sex"     => ($sex=="null" ? "" : $sex),
                          "variant" => ($variante=="null" ? "" : $variante)];
            $this->callUrl($method, $url, $modelData);
        } else {
            throw new Exception("Error at Cucumber Feature Definition. One of provided data (family=$family, line=$line or sex=$sex) is not valid because was not previously created at the system.");
        }
    }

}
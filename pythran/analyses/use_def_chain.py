""" UsedDefChain build used-define chains analysis for each variable. """

from pythran.analyses.imported_ids import ImportedIds
from pythran.analyses.globals_analysis import Globals
from pythran.passmanager import FunctionAnalysis, ModuleAnalysis
from pythran.syntax import PythranSyntaxError
import pythran.metadata as md

import beniget
from itertools import product
import gast as ast


class UseDefChains(ModuleAnalysis):

    """
    Build use-define chains analysis for each variable.
    """

    def __init__(self):
        self.result = None
        super(UseDefChains, self).__init__(DefUseChains)

    def visit_Module(self, node):
        udc = beniget.UseDefChains(self.def_use_chains)
        self.result = udc.chains

class DefUseChains(ModuleAnalysis):

    """
    Build define-use-define chains analysis for each variable.
    """

    def __init__(self):
        self.result = None
        super(DefUseChains, self).__init__()

    def visit_Module(self, node):
        duc = beniget.DefUseChains()
        duc.visit(node)
        self.result = duc

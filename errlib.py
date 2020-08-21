class CompileError(Exception):
    def __init__(self, message):
        self.message = message
    def __str__(self):
        return self.message

class ObjectNotFound(CompileError):
    def __init__(self, message):
        self.message = message

class PredicateNotFound(CompileError):
    def __init__(self, message):
        self.message = message

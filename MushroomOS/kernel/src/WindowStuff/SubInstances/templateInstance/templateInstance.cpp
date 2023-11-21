#include "templateInstance.h"
#include "../../../cmdParsing/cstrTools.h"
#include "../../../memory/heap.h"
#include "../../../kernelStuff/stuff/cstr.h"

TemplateInstance::TemplateInstance(Window* window){
    this->window = window;
    this->instanceType = InstanceType::Default;
}

void TemplateInstance::Init(){
    bgCol = 0x00000000;
    window->renderer->color = Colors.white;
    window->renderer->Clear(bgCol);
    window->renderer->putStr("String", (window->size.width-(12*8))/2, 30);
}

void TemplateInstance::Free()
{
    free(window);
}
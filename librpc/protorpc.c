#include <stdlib.h>
#include <stdio.h>

#include <ast_runtime.h>
#include <ast_debug.h>

#include "protorpc.h"

ast_err
Create_write(ast_runtime* rt, Create* create_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_string,1,&create_v->path);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&create_v->cmode);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&create_v->initialsz);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,4,&create_v->basepe);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<create_v->chunksizehint.count;i++) {
            status = ast_write_primitive(rt,ast_int64,5,&create_v->chunksizehint.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_int32,6,&create_v->use_parallel);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,7,&create_v->parameters);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Create_write*/

ast_err
Create_read(ast_runtime* rt, Create** create_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Create* create_v;
    unsigned long pos;

    create_v = (Create*)ast_alloc(rt,sizeof(Create));
    if(create_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Create|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_string,1,&create_v->path);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&create_v->cmode);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&create_v->initialsz);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_int32,4,&create_v->basepe);
            } break;
        case 5: {
            int64_t tmp;
            status = ast_read_primitive(rt,ast_int64,5,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int64,&create_v->chunksizehint,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_int32,6,&create_v->use_parallel);
            } break;
        case 7: {
            status = ast_read_primitive(rt,ast_bytes,7,&create_v->parameters);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(create_vp) *create_vp = create_v;
done:
    return ACATCH(status);
} /*Create_read*/

ast_err
Create_reclaim(ast_runtime* rt, Create* create_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,create_v->path);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_reclaim_bytes(rt,&create_v->parameters);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)create_v);
    goto done;

done:
    return ACATCH(status);

} /*Create_reclaim*/

size_t
Create_get_size(ast_runtime* rt, Create* create_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_string,&create_v->path);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&create_v->cmode);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&create_v->initialsz);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_int32,&create_v->basepe);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<create_v->chunksizehint.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,5);
            fieldsize += ast_get_size(rt,ast_int64,&create_v->chunksizehint.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_int32,&create_v->use_parallel);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,7);
        fieldsize += ast_get_size(rt,ast_bytes,&create_v->parameters);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Create_get_size*/

ast_err
Create_Return_write(ast_runtime* rt, Create_Return* create_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&create_return_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Create_Return_write*/

ast_err
Create_Return_read(ast_runtime* rt, Create_Return** create_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Create_Return* create_return_v;
    unsigned long pos;

    create_return_v = (Create_Return*)ast_alloc(rt,sizeof(Create_Return));
    if(create_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Create_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&create_return_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(create_return_vp) *create_return_vp = create_return_v;
done:
    return ACATCH(status);
} /*Create_Return_read*/

ast_err
Create_Return_reclaim(ast_runtime* rt, Create_Return* create_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)create_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Create_Return_reclaim*/

size_t
Create_Return_get_size(ast_runtime* rt, Create_Return* create_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&create_return_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Create_Return_get_size*/

ast_err
Open_write(ast_runtime* rt, Open* open_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_string,1,&open_v->path);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&open_v->mode);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&open_v->basepe);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<open_v->chunksizehint.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,4,&open_v->chunksizehint.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_int32,5,&open_v->use_parallel);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,6,&open_v->parameters);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Open_write*/

ast_err
Open_read(ast_runtime* rt, Open** open_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Open* open_v;
    unsigned long pos;

    open_v = (Open*)ast_alloc(rt,sizeof(Open));
    if(open_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Open|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_string,1,&open_v->path);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&open_v->mode);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&open_v->basepe);
            } break;
        case 4: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&open_v->chunksizehint,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_int32,5,&open_v->use_parallel);
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_bytes,6,&open_v->parameters);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(open_vp) *open_vp = open_v;
done:
    return ACATCH(status);
} /*Open_read*/

ast_err
Open_reclaim(ast_runtime* rt, Open* open_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,open_v->path);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_reclaim_bytes(rt,&open_v->parameters);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)open_v);
    goto done;

done:
    return ACATCH(status);

} /*Open_reclaim*/

size_t
Open_get_size(ast_runtime* rt, Open* open_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_string,&open_v->path);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&open_v->mode);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&open_v->basepe);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<open_v->chunksizehint.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_uint64,&open_v->chunksizehint.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_int32,&open_v->use_parallel);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_bytes,&open_v->parameters);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Open_get_size*/

ast_err
Open_Return_write(ast_runtime* rt, Open_Return* open_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&open_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&open_return_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Open_Return_write*/

ast_err
Open_Return_read(ast_runtime* rt, Open_Return** open_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Open_Return* open_return_v;
    unsigned long pos;

    open_return_v = (Open_Return*)ast_alloc(rt,sizeof(Open_Return));
    if(open_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Open_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&open_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&open_return_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(open_return_vp) *open_return_vp = open_return_v;
done:
    return ACATCH(status);
} /*Open_Return_read*/

ast_err
Open_Return_reclaim(ast_runtime* rt, Open_Return* open_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)open_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Open_Return_reclaim*/

size_t
Open_Return_get_size(ast_runtime* rt, Open_Return* open_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&open_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&open_return_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Open_Return_get_size*/

ast_err
Redef_write(ast_runtime* rt, Redef* redef_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&redef_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Redef_write*/

ast_err
Redef_read(ast_runtime* rt, Redef** redef_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Redef* redef_v;
    unsigned long pos;

    redef_v = (Redef*)ast_alloc(rt,sizeof(Redef));
    if(redef_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Redef|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&redef_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(redef_vp) *redef_vp = redef_v;
done:
    return ACATCH(status);
} /*Redef_read*/

ast_err
Redef_reclaim(ast_runtime* rt, Redef* redef_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)redef_v);
    goto done;

done:
    return ACATCH(status);

} /*Redef_reclaim*/

size_t
Redef_get_size(ast_runtime* rt, Redef* redef_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&redef_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Redef_get_size*/

ast_err
Redef_Return_write(ast_runtime* rt, Redef_Return* redef_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&redef_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Redef_Return_write*/

ast_err
Redef_Return_read(ast_runtime* rt, Redef_Return** redef_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Redef_Return* redef_return_v;
    unsigned long pos;

    redef_return_v = (Redef_Return*)ast_alloc(rt,sizeof(Redef_Return));
    if(redef_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Redef_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&redef_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(redef_return_vp) *redef_return_vp = redef_return_v;
done:
    return ACATCH(status);
} /*Redef_Return_read*/

ast_err
Redef_Return_reclaim(ast_runtime* rt, Redef_Return* redef_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)redef_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Redef_Return_reclaim*/

size_t
Redef_Return_get_size(ast_runtime* rt, Redef_Return* redef_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&redef_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Redef_Return_get_size*/

ast_err
_Enddef_write(ast_runtime* rt, _Enddef* _enddef_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&_enddef_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,2,&_enddef_v->minfree);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&_enddef_v->v_align);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,4,&_enddef_v->v_minfree);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,5,&_enddef_v->r_align);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*_Enddef_write*/

ast_err
_Enddef_read(ast_runtime* rt, _Enddef** _enddef_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    _Enddef* _enddef_v;
    unsigned long pos;

    _enddef_v = (_Enddef*)ast_alloc(rt,sizeof(_Enddef));
    if(_enddef_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|_Enddef|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&_enddef_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_uint64,2,&_enddef_v->minfree);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&_enddef_v->v_align);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_uint64,4,&_enddef_v->v_minfree);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_uint64,5,&_enddef_v->r_align);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(_enddef_vp) *_enddef_vp = _enddef_v;
done:
    return ACATCH(status);
} /*_Enddef_read*/

ast_err
_Enddef_reclaim(ast_runtime* rt, _Enddef* _enddef_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)_enddef_v);
    goto done;

done:
    return ACATCH(status);

} /*_Enddef_reclaim*/

size_t
_Enddef_get_size(ast_runtime* rt, _Enddef* _enddef_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&_enddef_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_uint64,&_enddef_v->minfree);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&_enddef_v->v_align);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_uint64,&_enddef_v->v_minfree);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_uint64,&_enddef_v->r_align);
        totalsize += fieldsize;
    }
    return totalsize;

} /*_Enddef_get_size*/

ast_err
_Enddef_Return_write(ast_runtime* rt, _Enddef_Return* _enddef_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&_enddef_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*_Enddef_Return_write*/

ast_err
_Enddef_Return_read(ast_runtime* rt, _Enddef_Return** _enddef_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    _Enddef_Return* _enddef_return_v;
    unsigned long pos;

    _enddef_return_v = (_Enddef_Return*)ast_alloc(rt,sizeof(_Enddef_Return));
    if(_enddef_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|_Enddef_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&_enddef_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(_enddef_return_vp) *_enddef_return_vp = _enddef_return_v;
done:
    return ACATCH(status);
} /*_Enddef_Return_read*/

ast_err
_Enddef_Return_reclaim(ast_runtime* rt, _Enddef_Return* _enddef_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)_enddef_return_v);
    goto done;

done:
    return ACATCH(status);

} /*_Enddef_Return_reclaim*/

size_t
_Enddef_Return_get_size(ast_runtime* rt, _Enddef_Return* _enddef_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&_enddef_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*_Enddef_Return_get_size*/

ast_err
Sync_write(ast_runtime* rt, Sync* sync_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&sync_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Sync_write*/

ast_err
Sync_read(ast_runtime* rt, Sync** sync_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Sync* sync_v;
    unsigned long pos;

    sync_v = (Sync*)ast_alloc(rt,sizeof(Sync));
    if(sync_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Sync|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&sync_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(sync_vp) *sync_vp = sync_v;
done:
    return ACATCH(status);
} /*Sync_read*/

ast_err
Sync_reclaim(ast_runtime* rt, Sync* sync_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)sync_v);
    goto done;

done:
    return ACATCH(status);

} /*Sync_reclaim*/

size_t
Sync_get_size(ast_runtime* rt, Sync* sync_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&sync_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Sync_get_size*/

ast_err
Sync_Return_write(ast_runtime* rt, Sync_Return* sync_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&sync_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Sync_Return_write*/

ast_err
Sync_Return_read(ast_runtime* rt, Sync_Return** sync_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Sync_Return* sync_return_v;
    unsigned long pos;

    sync_return_v = (Sync_Return*)ast_alloc(rt,sizeof(Sync_Return));
    if(sync_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Sync_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&sync_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(sync_return_vp) *sync_return_vp = sync_return_v;
done:
    return ACATCH(status);
} /*Sync_Return_read*/

ast_err
Sync_Return_reclaim(ast_runtime* rt, Sync_Return* sync_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)sync_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Sync_Return_reclaim*/

size_t
Sync_Return_get_size(ast_runtime* rt, Sync_Return* sync_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&sync_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Sync_Return_get_size*/

ast_err
Abort_write(ast_runtime* rt, Abort* abort_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&abort_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Abort_write*/

ast_err
Abort_read(ast_runtime* rt, Abort** abort_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Abort* abort_v;
    unsigned long pos;

    abort_v = (Abort*)ast_alloc(rt,sizeof(Abort));
    if(abort_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Abort|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&abort_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(abort_vp) *abort_vp = abort_v;
done:
    return ACATCH(status);
} /*Abort_read*/

ast_err
Abort_reclaim(ast_runtime* rt, Abort* abort_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)abort_v);
    goto done;

done:
    return ACATCH(status);

} /*Abort_reclaim*/

size_t
Abort_get_size(ast_runtime* rt, Abort* abort_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&abort_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Abort_get_size*/

ast_err
Abort_Return_write(ast_runtime* rt, Abort_Return* abort_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&abort_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Abort_Return_write*/

ast_err
Abort_Return_read(ast_runtime* rt, Abort_Return** abort_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Abort_Return* abort_return_v;
    unsigned long pos;

    abort_return_v = (Abort_Return*)ast_alloc(rt,sizeof(Abort_Return));
    if(abort_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Abort_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&abort_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(abort_return_vp) *abort_return_vp = abort_return_v;
done:
    return ACATCH(status);
} /*Abort_Return_read*/

ast_err
Abort_Return_reclaim(ast_runtime* rt, Abort_Return* abort_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)abort_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Abort_Return_reclaim*/

size_t
Abort_Return_get_size(ast_runtime* rt, Abort_Return* abort_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&abort_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Abort_Return_get_size*/

ast_err
Close_write(ast_runtime* rt, Close* close_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&close_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Close_write*/

ast_err
Close_read(ast_runtime* rt, Close** close_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Close* close_v;
    unsigned long pos;

    close_v = (Close*)ast_alloc(rt,sizeof(Close));
    if(close_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Close|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&close_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(close_vp) *close_vp = close_v;
done:
    return ACATCH(status);
} /*Close_read*/

ast_err
Close_reclaim(ast_runtime* rt, Close* close_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)close_v);
    goto done;

done:
    return ACATCH(status);

} /*Close_reclaim*/

size_t
Close_get_size(ast_runtime* rt, Close* close_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&close_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Close_get_size*/

ast_err
Close_Return_write(ast_runtime* rt, Close_Return* close_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&close_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Close_Return_write*/

ast_err
Close_Return_read(ast_runtime* rt, Close_Return** close_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Close_Return* close_return_v;
    unsigned long pos;

    close_return_v = (Close_Return*)ast_alloc(rt,sizeof(Close_Return));
    if(close_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Close_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&close_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(close_return_vp) *close_return_vp = close_return_v;
done:
    return ACATCH(status);
} /*Close_Return_read*/

ast_err
Close_Return_reclaim(ast_runtime* rt, Close_Return* close_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)close_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Close_Return_reclaim*/

size_t
Close_Return_get_size(ast_runtime* rt, Close_Return* close_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&close_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Close_Return_get_size*/

ast_err
Set_fill_write(ast_runtime* rt, Set_fill* set_fill_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&set_fill_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&set_fill_v->fillmode);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Set_fill_write*/

ast_err
Set_fill_read(ast_runtime* rt, Set_fill** set_fill_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Set_fill* set_fill_v;
    unsigned long pos;

    set_fill_v = (Set_fill*)ast_alloc(rt,sizeof(Set_fill));
    if(set_fill_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Set_fill|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&set_fill_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&set_fill_v->fillmode);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(set_fill_vp) *set_fill_vp = set_fill_v;
done:
    return ACATCH(status);
} /*Set_fill_read*/

ast_err
Set_fill_reclaim(ast_runtime* rt, Set_fill* set_fill_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)set_fill_v);
    goto done;

done:
    return ACATCH(status);

} /*Set_fill_reclaim*/

size_t
Set_fill_get_size(ast_runtime* rt, Set_fill* set_fill_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&set_fill_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&set_fill_v->fillmode);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Set_fill_get_size*/

ast_err
Set_fill_Return_write(ast_runtime* rt, Set_fill_Return* set_fill_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&set_fill_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&set_fill_return_v->oldmode);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Set_fill_Return_write*/

ast_err
Set_fill_Return_read(ast_runtime* rt, Set_fill_Return** set_fill_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Set_fill_Return* set_fill_return_v;
    unsigned long pos;

    set_fill_return_v = (Set_fill_Return*)ast_alloc(rt,sizeof(Set_fill_Return));
    if(set_fill_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Set_fill_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&set_fill_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&set_fill_return_v->oldmode);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(set_fill_return_vp) *set_fill_return_vp = set_fill_return_v;
done:
    return ACATCH(status);
} /*Set_fill_Return_read*/

ast_err
Set_fill_Return_reclaim(ast_runtime* rt, Set_fill_Return* set_fill_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)set_fill_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Set_fill_Return_reclaim*/

size_t
Set_fill_Return_get_size(ast_runtime* rt, Set_fill_Return* set_fill_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&set_fill_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&set_fill_return_v->oldmode);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Set_fill_Return_get_size*/

ast_err
Inq_base_pe_write(ast_runtime* rt, Inq_base_pe* inq_base_pe_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_base_pe_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_base_pe_write*/

ast_err
Inq_base_pe_read(ast_runtime* rt, Inq_base_pe** inq_base_pe_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_base_pe* inq_base_pe_v;
    unsigned long pos;

    inq_base_pe_v = (Inq_base_pe*)ast_alloc(rt,sizeof(Inq_base_pe));
    if(inq_base_pe_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_base_pe|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_base_pe_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_base_pe_vp) *inq_base_pe_vp = inq_base_pe_v;
done:
    return ACATCH(status);
} /*Inq_base_pe_read*/

ast_err
Inq_base_pe_reclaim(ast_runtime* rt, Inq_base_pe* inq_base_pe_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_base_pe_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_base_pe_reclaim*/

size_t
Inq_base_pe_get_size(ast_runtime* rt, Inq_base_pe* inq_base_pe_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_base_pe_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_base_pe_get_size*/

ast_err
Inq_base_pe_Return_write(ast_runtime* rt, Inq_base_pe_Return* inq_base_pe_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_base_pe_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_base_pe_return_v->pe);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_base_pe_Return_write*/

ast_err
Inq_base_pe_Return_read(ast_runtime* rt, Inq_base_pe_Return** inq_base_pe_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_base_pe_Return* inq_base_pe_return_v;
    unsigned long pos;

    inq_base_pe_return_v = (Inq_base_pe_Return*)ast_alloc(rt,sizeof(Inq_base_pe_Return));
    if(inq_base_pe_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_base_pe_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_base_pe_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_base_pe_return_v->pe);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_base_pe_return_vp) *inq_base_pe_return_vp = inq_base_pe_return_v;
done:
    return ACATCH(status);
} /*Inq_base_pe_Return_read*/

ast_err
Inq_base_pe_Return_reclaim(ast_runtime* rt, Inq_base_pe_Return* inq_base_pe_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_base_pe_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_base_pe_Return_reclaim*/

size_t
Inq_base_pe_Return_get_size(ast_runtime* rt, Inq_base_pe_Return* inq_base_pe_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_base_pe_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_base_pe_return_v->pe);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_base_pe_Return_get_size*/

ast_err
Set_base_pe_write(ast_runtime* rt, Set_base_pe* set_base_pe_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&set_base_pe_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&set_base_pe_v->pe);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Set_base_pe_write*/

ast_err
Set_base_pe_read(ast_runtime* rt, Set_base_pe** set_base_pe_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Set_base_pe* set_base_pe_v;
    unsigned long pos;

    set_base_pe_v = (Set_base_pe*)ast_alloc(rt,sizeof(Set_base_pe));
    if(set_base_pe_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Set_base_pe|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&set_base_pe_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&set_base_pe_v->pe);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(set_base_pe_vp) *set_base_pe_vp = set_base_pe_v;
done:
    return ACATCH(status);
} /*Set_base_pe_read*/

ast_err
Set_base_pe_reclaim(ast_runtime* rt, Set_base_pe* set_base_pe_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)set_base_pe_v);
    goto done;

done:
    return ACATCH(status);

} /*Set_base_pe_reclaim*/

size_t
Set_base_pe_get_size(ast_runtime* rt, Set_base_pe* set_base_pe_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&set_base_pe_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&set_base_pe_v->pe);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Set_base_pe_get_size*/

ast_err
Set_base_pe_Return_write(ast_runtime* rt, Set_base_pe_Return* set_base_pe_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&set_base_pe_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Set_base_pe_Return_write*/

ast_err
Set_base_pe_Return_read(ast_runtime* rt, Set_base_pe_Return** set_base_pe_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Set_base_pe_Return* set_base_pe_return_v;
    unsigned long pos;

    set_base_pe_return_v = (Set_base_pe_Return*)ast_alloc(rt,sizeof(Set_base_pe_Return));
    if(set_base_pe_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Set_base_pe_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&set_base_pe_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(set_base_pe_return_vp) *set_base_pe_return_vp = set_base_pe_return_v;
done:
    return ACATCH(status);
} /*Set_base_pe_Return_read*/

ast_err
Set_base_pe_Return_reclaim(ast_runtime* rt, Set_base_pe_Return* set_base_pe_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)set_base_pe_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Set_base_pe_Return_reclaim*/

size_t
Set_base_pe_Return_get_size(ast_runtime* rt, Set_base_pe_Return* set_base_pe_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&set_base_pe_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Set_base_pe_Return_get_size*/

ast_err
Inq_format_write(ast_runtime* rt, Inq_format* inq_format_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_format_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_format_write*/

ast_err
Inq_format_read(ast_runtime* rt, Inq_format** inq_format_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_format* inq_format_v;
    unsigned long pos;

    inq_format_v = (Inq_format*)ast_alloc(rt,sizeof(Inq_format));
    if(inq_format_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_format|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_format_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_format_vp) *inq_format_vp = inq_format_v;
done:
    return ACATCH(status);
} /*Inq_format_read*/

ast_err
Inq_format_reclaim(ast_runtime* rt, Inq_format* inq_format_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_format_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_format_reclaim*/

size_t
Inq_format_get_size(ast_runtime* rt, Inq_format* inq_format_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_format_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_format_get_size*/

ast_err
Inq_format_Return_write(ast_runtime* rt, Inq_format_Return* inq_format_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_format_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_format_return_v->format);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_format_Return_write*/

ast_err
Inq_format_Return_read(ast_runtime* rt, Inq_format_Return** inq_format_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_format_Return* inq_format_return_v;
    unsigned long pos;

    inq_format_return_v = (Inq_format_Return*)ast_alloc(rt,sizeof(Inq_format_Return));
    if(inq_format_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_format_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_format_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_format_return_v->format);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_format_return_vp) *inq_format_return_vp = inq_format_return_v;
done:
    return ACATCH(status);
} /*Inq_format_Return_read*/

ast_err
Inq_format_Return_reclaim(ast_runtime* rt, Inq_format_Return* inq_format_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_format_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_format_Return_reclaim*/

size_t
Inq_format_Return_get_size(ast_runtime* rt, Inq_format_Return* inq_format_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_format_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_format_return_v->format);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_format_Return_get_size*/

ast_err
Inq_write(ast_runtime* rt, Inq* inq_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_write*/

ast_err
Inq_read(ast_runtime* rt, Inq** inq_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq* inq_v;
    unsigned long pos;

    inq_v = (Inq*)ast_alloc(rt,sizeof(Inq));
    if(inq_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_vp) *inq_vp = inq_v;
done:
    return ACATCH(status);
} /*Inq_read*/

ast_err
Inq_reclaim(ast_runtime* rt, Inq* inq_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_reclaim*/

size_t
Inq_get_size(ast_runtime* rt, Inq* inq_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_get_size*/

ast_err
Inq_Return_write(ast_runtime* rt, Inq_Return* inq_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_return_v->ndims);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&inq_return_v->nvars);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,4,&inq_return_v->natts);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,5,&inq_return_v->unlimdimid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_Return_write*/

ast_err
Inq_Return_read(ast_runtime* rt, Inq_Return** inq_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_Return* inq_return_v;
    unsigned long pos;

    inq_return_v = (Inq_Return*)ast_alloc(rt,sizeof(Inq_Return));
    if(inq_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_return_v->ndims);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&inq_return_v->nvars);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_int32,4,&inq_return_v->natts);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_int32,5,&inq_return_v->unlimdimid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_return_vp) *inq_return_vp = inq_return_v;
done:
    return ACATCH(status);
} /*Inq_Return_read*/

ast_err
Inq_Return_reclaim(ast_runtime* rt, Inq_Return* inq_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_Return_reclaim*/

size_t
Inq_Return_get_size(ast_runtime* rt, Inq_Return* inq_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_return_v->ndims);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&inq_return_v->nvars);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_int32,&inq_return_v->natts);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_int32,&inq_return_v->unlimdimid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_Return_get_size*/

ast_err
Inq_type_write(ast_runtime* rt, Inq_type* inq_type_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_type_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_type_v->xtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_type_write*/

ast_err
Inq_type_read(ast_runtime* rt, Inq_type** inq_type_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_type* inq_type_v;
    unsigned long pos;

    inq_type_v = (Inq_type*)ast_alloc(rt,sizeof(Inq_type));
    if(inq_type_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_type|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_type_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_type_v->xtype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_type_vp) *inq_type_vp = inq_type_v;
done:
    return ACATCH(status);
} /*Inq_type_read*/

ast_err
Inq_type_reclaim(ast_runtime* rt, Inq_type* inq_type_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_type_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_type_reclaim*/

size_t
Inq_type_get_size(ast_runtime* rt, Inq_type* inq_type_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_type_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_type_v->xtype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_type_get_size*/

ast_err
Inq_type_Return_write(ast_runtime* rt, Inq_type_Return* inq_type_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_type_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_type_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&inq_type_return_v->size);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_type_Return_write*/

ast_err
Inq_type_Return_read(ast_runtime* rt, Inq_type_Return** inq_type_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_type_Return* inq_type_return_v;
    unsigned long pos;

    inq_type_return_v = (Inq_type_Return*)ast_alloc(rt,sizeof(Inq_type_Return));
    if(inq_type_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_type_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_type_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_type_return_v->name);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&inq_type_return_v->size);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_type_return_vp) *inq_type_return_vp = inq_type_return_v;
done:
    return ACATCH(status);
} /*Inq_type_Return_read*/

ast_err
Inq_type_Return_reclaim(ast_runtime* rt, Inq_type_Return* inq_type_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_type_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_type_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_type_Return_reclaim*/

size_t
Inq_type_Return_get_size(ast_runtime* rt, Inq_type_Return* inq_type_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_type_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_type_return_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&inq_type_return_v->size);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_type_Return_get_size*/

ast_err
Def_dim_write(ast_runtime* rt, Def_dim* def_dim_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_dim_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&def_dim_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&def_dim_v->len);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_dim_write*/

ast_err
Def_dim_read(ast_runtime* rt, Def_dim** def_dim_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_dim* def_dim_v;
    unsigned long pos;

    def_dim_v = (Def_dim*)ast_alloc(rt,sizeof(Def_dim));
    if(def_dim_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_dim|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_dim_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&def_dim_v->name);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&def_dim_v->len);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_dim_vp) *def_dim_vp = def_dim_v;
done:
    return ACATCH(status);
} /*Def_dim_read*/

ast_err
Def_dim_reclaim(ast_runtime* rt, Def_dim* def_dim_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,def_dim_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)def_dim_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_dim_reclaim*/

size_t
Def_dim_get_size(ast_runtime* rt, Def_dim* def_dim_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_dim_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&def_dim_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&def_dim_v->len);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_dim_get_size*/

ast_err
Def_dim_Return_write(ast_runtime* rt, Def_dim_Return* def_dim_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_dim_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_dim_return_v->dimid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_dim_Return_write*/

ast_err
Def_dim_Return_read(ast_runtime* rt, Def_dim_Return** def_dim_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_dim_Return* def_dim_return_v;
    unsigned long pos;

    def_dim_return_v = (Def_dim_Return*)ast_alloc(rt,sizeof(Def_dim_Return));
    if(def_dim_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_dim_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_dim_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_dim_return_v->dimid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_dim_return_vp) *def_dim_return_vp = def_dim_return_v;
done:
    return ACATCH(status);
} /*Def_dim_Return_read*/

ast_err
Def_dim_Return_reclaim(ast_runtime* rt, Def_dim_Return* def_dim_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_dim_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_dim_Return_reclaim*/

size_t
Def_dim_Return_get_size(ast_runtime* rt, Def_dim_Return* def_dim_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_dim_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_dim_return_v->dimid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_dim_Return_get_size*/

ast_err
Inq_dimid_write(ast_runtime* rt, Inq_dimid* inq_dimid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_dimid_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_dimid_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_dimid_write*/

ast_err
Inq_dimid_read(ast_runtime* rt, Inq_dimid** inq_dimid_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_dimid* inq_dimid_v;
    unsigned long pos;

    inq_dimid_v = (Inq_dimid*)ast_alloc(rt,sizeof(Inq_dimid));
    if(inq_dimid_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_dimid|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_dimid_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_dimid_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_dimid_vp) *inq_dimid_vp = inq_dimid_v;
done:
    return ACATCH(status);
} /*Inq_dimid_read*/

ast_err
Inq_dimid_reclaim(ast_runtime* rt, Inq_dimid* inq_dimid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_dimid_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_dimid_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_dimid_reclaim*/

size_t
Inq_dimid_get_size(ast_runtime* rt, Inq_dimid* inq_dimid_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dimid_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_dimid_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_dimid_get_size*/

ast_err
Inq_dimid_Return_write(ast_runtime* rt, Inq_dimid_Return* inq_dimid_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_dimid_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_dimid_return_v->dimid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_dimid_Return_write*/

ast_err
Inq_dimid_Return_read(ast_runtime* rt, Inq_dimid_Return** inq_dimid_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_dimid_Return* inq_dimid_return_v;
    unsigned long pos;

    inq_dimid_return_v = (Inq_dimid_Return*)ast_alloc(rt,sizeof(Inq_dimid_Return));
    if(inq_dimid_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_dimid_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_dimid_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_dimid_return_v->dimid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_dimid_return_vp) *inq_dimid_return_vp = inq_dimid_return_v;
done:
    return ACATCH(status);
} /*Inq_dimid_Return_read*/

ast_err
Inq_dimid_Return_reclaim(ast_runtime* rt, Inq_dimid_Return* inq_dimid_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_dimid_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_dimid_Return_reclaim*/

size_t
Inq_dimid_Return_get_size(ast_runtime* rt, Inq_dimid_Return* inq_dimid_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dimid_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dimid_return_v->dimid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_dimid_Return_get_size*/

ast_err
Inq_dim_write(ast_runtime* rt, Inq_dim* inq_dim_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_dim_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_dim_v->dimid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_dim_write*/

ast_err
Inq_dim_read(ast_runtime* rt, Inq_dim** inq_dim_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_dim* inq_dim_v;
    unsigned long pos;

    inq_dim_v = (Inq_dim*)ast_alloc(rt,sizeof(Inq_dim));
    if(inq_dim_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_dim|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_dim_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_dim_v->dimid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_dim_vp) *inq_dim_vp = inq_dim_v;
done:
    return ACATCH(status);
} /*Inq_dim_read*/

ast_err
Inq_dim_reclaim(ast_runtime* rt, Inq_dim* inq_dim_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_dim_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_dim_reclaim*/

size_t
Inq_dim_get_size(ast_runtime* rt, Inq_dim* inq_dim_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dim_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dim_v->dimid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_dim_get_size*/

ast_err
Inq_dim_Return_write(ast_runtime* rt, Inq_dim_Return* inq_dim_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_dim_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_dim_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&inq_dim_return_v->len);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_dim_Return_write*/

ast_err
Inq_dim_Return_read(ast_runtime* rt, Inq_dim_Return** inq_dim_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_dim_Return* inq_dim_return_v;
    unsigned long pos;

    inq_dim_return_v = (Inq_dim_Return*)ast_alloc(rt,sizeof(Inq_dim_Return));
    if(inq_dim_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_dim_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_dim_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_dim_return_v->name);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&inq_dim_return_v->len);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_dim_return_vp) *inq_dim_return_vp = inq_dim_return_v;
done:
    return ACATCH(status);
} /*Inq_dim_Return_read*/

ast_err
Inq_dim_Return_reclaim(ast_runtime* rt, Inq_dim_Return* inq_dim_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_dim_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_dim_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_dim_Return_reclaim*/

size_t
Inq_dim_Return_get_size(ast_runtime* rt, Inq_dim_Return* inq_dim_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dim_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_dim_return_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&inq_dim_return_v->len);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_dim_Return_get_size*/

ast_err
Inq_unlimdim_write(ast_runtime* rt, Inq_unlimdim* inq_unlimdim_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_unlimdim_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_unlimdim_write*/

ast_err
Inq_unlimdim_read(ast_runtime* rt, Inq_unlimdim** inq_unlimdim_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_unlimdim* inq_unlimdim_v;
    unsigned long pos;

    inq_unlimdim_v = (Inq_unlimdim*)ast_alloc(rt,sizeof(Inq_unlimdim));
    if(inq_unlimdim_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_unlimdim|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_unlimdim_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_unlimdim_vp) *inq_unlimdim_vp = inq_unlimdim_v;
done:
    return ACATCH(status);
} /*Inq_unlimdim_read*/

ast_err
Inq_unlimdim_reclaim(ast_runtime* rt, Inq_unlimdim* inq_unlimdim_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_unlimdim_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_unlimdim_reclaim*/

size_t
Inq_unlimdim_get_size(ast_runtime* rt, Inq_unlimdim* inq_unlimdim_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_unlimdim_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_unlimdim_get_size*/

ast_err
Inq_unlimdim_Return_write(ast_runtime* rt, Inq_unlimdim_Return* inq_unlimdim_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_unlimdim_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_unlimdim_return_v->unlimdimid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_unlimdim_Return_write*/

ast_err
Inq_unlimdim_Return_read(ast_runtime* rt, Inq_unlimdim_Return** inq_unlimdim_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_unlimdim_Return* inq_unlimdim_return_v;
    unsigned long pos;

    inq_unlimdim_return_v = (Inq_unlimdim_Return*)ast_alloc(rt,sizeof(Inq_unlimdim_Return));
    if(inq_unlimdim_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_unlimdim_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_unlimdim_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_unlimdim_return_v->unlimdimid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_unlimdim_return_vp) *inq_unlimdim_return_vp = inq_unlimdim_return_v;
done:
    return ACATCH(status);
} /*Inq_unlimdim_Return_read*/

ast_err
Inq_unlimdim_Return_reclaim(ast_runtime* rt, Inq_unlimdim_Return* inq_unlimdim_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_unlimdim_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_unlimdim_Return_reclaim*/

size_t
Inq_unlimdim_Return_get_size(ast_runtime* rt, Inq_unlimdim_Return* inq_unlimdim_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_unlimdim_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_unlimdim_return_v->unlimdimid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_unlimdim_Return_get_size*/

ast_err
Rename_dim_write(ast_runtime* rt, Rename_dim* rename_dim_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&rename_dim_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&rename_dim_v->dimid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&rename_dim_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Rename_dim_write*/

ast_err
Rename_dim_read(ast_runtime* rt, Rename_dim** rename_dim_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Rename_dim* rename_dim_v;
    unsigned long pos;

    rename_dim_v = (Rename_dim*)ast_alloc(rt,sizeof(Rename_dim));
    if(rename_dim_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Rename_dim|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&rename_dim_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&rename_dim_v->dimid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&rename_dim_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(rename_dim_vp) *rename_dim_vp = rename_dim_v;
done:
    return ACATCH(status);
} /*Rename_dim_read*/

ast_err
Rename_dim_reclaim(ast_runtime* rt, Rename_dim* rename_dim_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,rename_dim_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)rename_dim_v);
    goto done;

done:
    return ACATCH(status);

} /*Rename_dim_reclaim*/

size_t
Rename_dim_get_size(ast_runtime* rt, Rename_dim* rename_dim_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&rename_dim_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&rename_dim_v->dimid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&rename_dim_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Rename_dim_get_size*/

ast_err
Rename_dim_Return_write(ast_runtime* rt, Rename_dim_Return* rename_dim_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&rename_dim_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Rename_dim_Return_write*/

ast_err
Rename_dim_Return_read(ast_runtime* rt, Rename_dim_Return** rename_dim_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Rename_dim_Return* rename_dim_return_v;
    unsigned long pos;

    rename_dim_return_v = (Rename_dim_Return*)ast_alloc(rt,sizeof(Rename_dim_Return));
    if(rename_dim_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Rename_dim_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&rename_dim_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(rename_dim_return_vp) *rename_dim_return_vp = rename_dim_return_v;
done:
    return ACATCH(status);
} /*Rename_dim_Return_read*/

ast_err
Rename_dim_Return_reclaim(ast_runtime* rt, Rename_dim_Return* rename_dim_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)rename_dim_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Rename_dim_Return_reclaim*/

size_t
Rename_dim_Return_get_size(ast_runtime* rt, Rename_dim_Return* rename_dim_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&rename_dim_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Rename_dim_Return_get_size*/

ast_err
Inq_att_write(ast_runtime* rt, Inq_att* inq_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_att_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_att_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&inq_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_att_write*/

ast_err
Inq_att_read(ast_runtime* rt, Inq_att** inq_att_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_att* inq_att_v;
    unsigned long pos;

    inq_att_v = (Inq_att*)ast_alloc(rt,sizeof(Inq_att));
    if(inq_att_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_att|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_att_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_att_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&inq_att_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_att_vp) *inq_att_vp = inq_att_v;
done:
    return ACATCH(status);
} /*Inq_att_read*/

ast_err
Inq_att_reclaim(ast_runtime* rt, Inq_att* inq_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_att_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_att_reclaim*/

size_t
Inq_att_get_size(ast_runtime* rt, Inq_att* inq_att_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_att_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_att_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&inq_att_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_att_get_size*/

ast_err
Inq_att_Return_write(ast_runtime* rt, Inq_att_Return* inq_att_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_att_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_att_return_v->xtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&inq_att_return_v->len);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_att_Return_write*/

ast_err
Inq_att_Return_read(ast_runtime* rt, Inq_att_Return** inq_att_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_att_Return* inq_att_return_v;
    unsigned long pos;

    inq_att_return_v = (Inq_att_Return*)ast_alloc(rt,sizeof(Inq_att_Return));
    if(inq_att_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_att_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_att_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_att_return_v->xtype);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&inq_att_return_v->len);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_att_return_vp) *inq_att_return_vp = inq_att_return_v;
done:
    return ACATCH(status);
} /*Inq_att_Return_read*/

ast_err
Inq_att_Return_reclaim(ast_runtime* rt, Inq_att_Return* inq_att_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_att_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_att_Return_reclaim*/

size_t
Inq_att_Return_get_size(ast_runtime* rt, Inq_att_Return* inq_att_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_att_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_att_return_v->xtype);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&inq_att_return_v->len);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_att_Return_get_size*/

ast_err
Inq_attid_write(ast_runtime* rt, Inq_attid* inq_attid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_attid_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_attid_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&inq_attid_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_attid_write*/

ast_err
Inq_attid_read(ast_runtime* rt, Inq_attid** inq_attid_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_attid* inq_attid_v;
    unsigned long pos;

    inq_attid_v = (Inq_attid*)ast_alloc(rt,sizeof(Inq_attid));
    if(inq_attid_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_attid|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_attid_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_attid_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&inq_attid_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_attid_vp) *inq_attid_vp = inq_attid_v;
done:
    return ACATCH(status);
} /*Inq_attid_read*/

ast_err
Inq_attid_reclaim(ast_runtime* rt, Inq_attid* inq_attid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_attid_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_attid_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_attid_reclaim*/

size_t
Inq_attid_get_size(ast_runtime* rt, Inq_attid* inq_attid_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_attid_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_attid_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&inq_attid_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_attid_get_size*/

ast_err
Inq_attid_Return_write(ast_runtime* rt, Inq_attid_Return* inq_attid_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_attid_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_attid_return_v->attid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_attid_Return_write*/

ast_err
Inq_attid_Return_read(ast_runtime* rt, Inq_attid_Return** inq_attid_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_attid_Return* inq_attid_return_v;
    unsigned long pos;

    inq_attid_return_v = (Inq_attid_Return*)ast_alloc(rt,sizeof(Inq_attid_Return));
    if(inq_attid_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_attid_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_attid_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_attid_return_v->attid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_attid_return_vp) *inq_attid_return_vp = inq_attid_return_v;
done:
    return ACATCH(status);
} /*Inq_attid_Return_read*/

ast_err
Inq_attid_Return_reclaim(ast_runtime* rt, Inq_attid_Return* inq_attid_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_attid_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_attid_Return_reclaim*/

size_t
Inq_attid_Return_get_size(ast_runtime* rt, Inq_attid_Return* inq_attid_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_attid_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_attid_return_v->attid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_attid_Return_get_size*/

ast_err
Inq_attname_write(ast_runtime* rt, Inq_attname* inq_attname_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_attname_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_attname_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&inq_attname_v->attnum);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_attname_write*/

ast_err
Inq_attname_read(ast_runtime* rt, Inq_attname** inq_attname_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_attname* inq_attname_v;
    unsigned long pos;

    inq_attname_v = (Inq_attname*)ast_alloc(rt,sizeof(Inq_attname));
    if(inq_attname_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_attname|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_attname_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_attname_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&inq_attname_v->attnum);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_attname_vp) *inq_attname_vp = inq_attname_v;
done:
    return ACATCH(status);
} /*Inq_attname_read*/

ast_err
Inq_attname_reclaim(ast_runtime* rt, Inq_attname* inq_attname_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_attname_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_attname_reclaim*/

size_t
Inq_attname_get_size(ast_runtime* rt, Inq_attname* inq_attname_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_attname_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_attname_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&inq_attname_v->attnum);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_attname_get_size*/

ast_err
Inq_attname_Return_write(ast_runtime* rt, Inq_attname_Return* inq_attname_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_attname_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_attname_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_attname_Return_write*/

ast_err
Inq_attname_Return_read(ast_runtime* rt, Inq_attname_Return** inq_attname_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_attname_Return* inq_attname_return_v;
    unsigned long pos;

    inq_attname_return_v = (Inq_attname_Return*)ast_alloc(rt,sizeof(Inq_attname_Return));
    if(inq_attname_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_attname_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_attname_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_attname_return_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_attname_return_vp) *inq_attname_return_vp = inq_attname_return_v;
done:
    return ACATCH(status);
} /*Inq_attname_Return_read*/

ast_err
Inq_attname_Return_reclaim(ast_runtime* rt, Inq_attname_Return* inq_attname_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_attname_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_attname_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_attname_Return_reclaim*/

size_t
Inq_attname_Return_get_size(ast_runtime* rt, Inq_attname_Return* inq_attname_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_attname_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_attname_return_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_attname_Return_get_size*/

ast_err
Rename_att_write(ast_runtime* rt, Rename_att* rename_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&rename_att_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&rename_att_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&rename_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,4,&rename_att_v->newname);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Rename_att_write*/

ast_err
Rename_att_read(ast_runtime* rt, Rename_att** rename_att_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Rename_att* rename_att_v;
    unsigned long pos;

    rename_att_v = (Rename_att*)ast_alloc(rt,sizeof(Rename_att));
    if(rename_att_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Rename_att|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&rename_att_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&rename_att_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&rename_att_v->name);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_string,4,&rename_att_v->newname);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(rename_att_vp) *rename_att_vp = rename_att_v;
done:
    return ACATCH(status);
} /*Rename_att_read*/

ast_err
Rename_att_reclaim(ast_runtime* rt, Rename_att* rename_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,rename_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_reclaim_string(rt,rename_att_v->newname);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)rename_att_v);
    goto done;

done:
    return ACATCH(status);

} /*Rename_att_reclaim*/

size_t
Rename_att_get_size(ast_runtime* rt, Rename_att* rename_att_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&rename_att_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&rename_att_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&rename_att_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_string,&rename_att_v->newname);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Rename_att_get_size*/

ast_err
Rename_att_Return_write(ast_runtime* rt, Rename_att_Return* rename_att_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&rename_att_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Rename_att_Return_write*/

ast_err
Rename_att_Return_read(ast_runtime* rt, Rename_att_Return** rename_att_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Rename_att_Return* rename_att_return_v;
    unsigned long pos;

    rename_att_return_v = (Rename_att_Return*)ast_alloc(rt,sizeof(Rename_att_Return));
    if(rename_att_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Rename_att_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&rename_att_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(rename_att_return_vp) *rename_att_return_vp = rename_att_return_v;
done:
    return ACATCH(status);
} /*Rename_att_Return_read*/

ast_err
Rename_att_Return_reclaim(ast_runtime* rt, Rename_att_Return* rename_att_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)rename_att_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Rename_att_Return_reclaim*/

size_t
Rename_att_Return_get_size(ast_runtime* rt, Rename_att_Return* rename_att_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&rename_att_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Rename_att_Return_get_size*/

ast_err
Del_att_write(ast_runtime* rt, Del_att* del_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&del_att_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&del_att_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&del_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Del_att_write*/

ast_err
Del_att_read(ast_runtime* rt, Del_att** del_att_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Del_att* del_att_v;
    unsigned long pos;

    del_att_v = (Del_att*)ast_alloc(rt,sizeof(Del_att));
    if(del_att_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Del_att|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&del_att_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&del_att_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&del_att_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(del_att_vp) *del_att_vp = del_att_v;
done:
    return ACATCH(status);
} /*Del_att_read*/

ast_err
Del_att_reclaim(ast_runtime* rt, Del_att* del_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,del_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)del_att_v);
    goto done;

done:
    return ACATCH(status);

} /*Del_att_reclaim*/

size_t
Del_att_get_size(ast_runtime* rt, Del_att* del_att_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&del_att_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&del_att_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&del_att_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Del_att_get_size*/

ast_err
Del_att_Return_write(ast_runtime* rt, Del_att_Return* del_att_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&del_att_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Del_att_Return_write*/

ast_err
Del_att_Return_read(ast_runtime* rt, Del_att_Return** del_att_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Del_att_Return* del_att_return_v;
    unsigned long pos;

    del_att_return_v = (Del_att_Return*)ast_alloc(rt,sizeof(Del_att_Return));
    if(del_att_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Del_att_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&del_att_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(del_att_return_vp) *del_att_return_vp = del_att_return_v;
done:
    return ACATCH(status);
} /*Del_att_Return_read*/

ast_err
Del_att_Return_reclaim(ast_runtime* rt, Del_att_Return* del_att_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)del_att_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Del_att_Return_reclaim*/

size_t
Del_att_Return_get_size(ast_runtime* rt, Del_att_Return* del_att_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&del_att_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Del_att_Return_get_size*/

ast_err
Get_att_write(ast_runtime* rt, Get_att* get_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_att_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&get_att_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&get_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,4,&get_att_v->xtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_att_write*/

ast_err
Get_att_read(ast_runtime* rt, Get_att** get_att_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_att* get_att_v;
    unsigned long pos;

    get_att_v = (Get_att*)ast_alloc(rt,sizeof(Get_att));
    if(get_att_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_att|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_att_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&get_att_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&get_att_v->name);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_int32,4,&get_att_v->xtype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_att_vp) *get_att_vp = get_att_v;
done:
    return ACATCH(status);
} /*Get_att_read*/

ast_err
Get_att_reclaim(ast_runtime* rt, Get_att* get_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,get_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)get_att_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_att_reclaim*/

size_t
Get_att_get_size(ast_runtime* rt, Get_att* get_att_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_att_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&get_att_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&get_att_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_int32,&get_att_v->xtype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_att_get_size*/

ast_err
Get_att_Return_write(ast_runtime* rt, Get_att_Return* get_att_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_att_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,2,&get_att_return_v->values);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_att_Return_write*/

ast_err
Get_att_Return_read(ast_runtime* rt, Get_att_Return** get_att_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_att_Return* get_att_return_v;
    unsigned long pos;

    get_att_return_v = (Get_att_Return*)ast_alloc(rt,sizeof(Get_att_Return));
    if(get_att_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_att_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_att_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_bytes,2,&get_att_return_v->values);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_att_return_vp) *get_att_return_vp = get_att_return_v;
done:
    return ACATCH(status);
} /*Get_att_Return_read*/

ast_err
Get_att_Return_reclaim(ast_runtime* rt, Get_att_Return* get_att_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&get_att_return_v->values);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)get_att_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_att_Return_reclaim*/

size_t
Get_att_Return_get_size(ast_runtime* rt, Get_att_Return* get_att_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_att_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_bytes,&get_att_return_v->values);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_att_Return_get_size*/

ast_err
Put_att_write(ast_runtime* rt, Put_att* put_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_att_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&put_att_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&put_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,4,&put_att_v->vtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,5,&put_att_v->nelems);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,6,&put_att_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,7,&put_att_v->atype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_att_write*/

ast_err
Put_att_read(ast_runtime* rt, Put_att** put_att_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_att* put_att_v;
    unsigned long pos;

    put_att_v = (Put_att*)ast_alloc(rt,sizeof(Put_att));
    if(put_att_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_att|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_att_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&put_att_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&put_att_v->name);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_int32,4,&put_att_v->vtype);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_uint64,5,&put_att_v->nelems);
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_bytes,6,&put_att_v->value);
            } break;
        case 7: {
            status = ast_read_primitive(rt,ast_int32,7,&put_att_v->atype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_att_vp) *put_att_vp = put_att_v;
done:
    return ACATCH(status);
} /*Put_att_read*/

ast_err
Put_att_reclaim(ast_runtime* rt, Put_att* put_att_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,put_att_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_reclaim_bytes(rt,&put_att_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)put_att_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_att_reclaim*/

size_t
Put_att_get_size(ast_runtime* rt, Put_att* put_att_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_att_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&put_att_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&put_att_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_int32,&put_att_v->vtype);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_uint64,&put_att_v->nelems);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_bytes,&put_att_v->value);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,7);
        fieldsize += ast_get_size(rt,ast_int32,&put_att_v->atype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_att_get_size*/

ast_err
Put_att_Return_write(ast_runtime* rt, Put_att_Return* put_att_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_att_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_att_Return_write*/

ast_err
Put_att_Return_read(ast_runtime* rt, Put_att_Return** put_att_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_att_Return* put_att_return_v;
    unsigned long pos;

    put_att_return_v = (Put_att_Return*)ast_alloc(rt,sizeof(Put_att_Return));
    if(put_att_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_att_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_att_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_att_return_vp) *put_att_return_vp = put_att_return_v;
done:
    return ACATCH(status);
} /*Put_att_Return_read*/

ast_err
Put_att_Return_reclaim(ast_runtime* rt, Put_att_Return* put_att_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)put_att_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_att_Return_reclaim*/

size_t
Put_att_Return_get_size(ast_runtime* rt, Put_att_Return* put_att_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_att_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_att_Return_get_size*/

ast_err
Def_var_write(ast_runtime* rt, Def_var* def_var_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&def_var_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&def_var_v->xtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,4,&def_var_v->ndims);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<def_var_v->dimids.count;i++) {
            status = ast_write_primitive(rt,ast_int32,5,&def_var_v->dimids.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Def_var_write*/

ast_err
Def_var_read(ast_runtime* rt, Def_var** def_var_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var* def_var_v;
    unsigned long pos;

    def_var_v = (Def_var*)ast_alloc(rt,sizeof(Def_var));
    if(def_var_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&def_var_v->name);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&def_var_v->xtype);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_int32,4,&def_var_v->ndims);
            } break;
        case 5: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,5,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&def_var_v->dimids,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_vp) *def_var_vp = def_var_v;
done:
    return ACATCH(status);
} /*Def_var_read*/

ast_err
Def_var_reclaim(ast_runtime* rt, Def_var* def_var_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,def_var_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)def_var_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_reclaim*/

size_t
Def_var_get_size(ast_runtime* rt, Def_var* def_var_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&def_var_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_v->xtype);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_v->ndims);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<def_var_v->dimids.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,5);
            fieldsize += ast_get_size(rt,ast_int32,&def_var_v->dimids.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_get_size*/

ast_err
Def_var_Return_write(ast_runtime* rt, Def_var_Return* def_var_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_var_return_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_Return_write*/

ast_err
Def_var_Return_read(ast_runtime* rt, Def_var_Return** def_var_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_Return* def_var_return_v;
    unsigned long pos;

    def_var_return_v = (Def_var_Return*)ast_alloc(rt,sizeof(Def_var_Return));
    if(def_var_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_var_return_v->varid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_return_vp) *def_var_return_vp = def_var_return_v;
done:
    return ACATCH(status);
} /*Def_var_Return_read*/

ast_err
Def_var_Return_reclaim(ast_runtime* rt, Def_var_Return* def_var_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_Return_reclaim*/

size_t
Def_var_Return_get_size(ast_runtime* rt, Def_var_Return* def_var_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_return_v->varid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_Return_get_size*/

ast_err
Inq_varid_write(ast_runtime* rt, Inq_varid* inq_varid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_varid_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_varid_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_varid_write*/

ast_err
Inq_varid_read(ast_runtime* rt, Inq_varid** inq_varid_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_varid* inq_varid_v;
    unsigned long pos;

    inq_varid_v = (Inq_varid*)ast_alloc(rt,sizeof(Inq_varid));
    if(inq_varid_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_varid|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_varid_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_varid_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_varid_vp) *inq_varid_vp = inq_varid_v;
done:
    return ACATCH(status);
} /*Inq_varid_read*/

ast_err
Inq_varid_reclaim(ast_runtime* rt, Inq_varid* inq_varid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_varid_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_varid_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_varid_reclaim*/

size_t
Inq_varid_get_size(ast_runtime* rt, Inq_varid* inq_varid_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_varid_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_varid_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_varid_get_size*/

ast_err
Inq_varid_Return_write(ast_runtime* rt, Inq_varid_Return* inq_varid_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_varid_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_varid_return_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_varid_Return_write*/

ast_err
Inq_varid_Return_read(ast_runtime* rt, Inq_varid_Return** inq_varid_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_varid_Return* inq_varid_return_v;
    unsigned long pos;

    inq_varid_return_v = (Inq_varid_Return*)ast_alloc(rt,sizeof(Inq_varid_Return));
    if(inq_varid_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_varid_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_varid_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_varid_return_v->varid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_varid_return_vp) *inq_varid_return_vp = inq_varid_return_v;
done:
    return ACATCH(status);
} /*Inq_varid_Return_read*/

ast_err
Inq_varid_Return_reclaim(ast_runtime* rt, Inq_varid_Return* inq_varid_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_varid_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_varid_Return_reclaim*/

size_t
Inq_varid_Return_get_size(ast_runtime* rt, Inq_varid_Return* inq_varid_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_varid_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_varid_return_v->varid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_varid_Return_get_size*/

ast_err
Rename_var_write(ast_runtime* rt, Rename_var* rename_var_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&rename_var_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&rename_var_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&rename_var_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Rename_var_write*/

ast_err
Rename_var_read(ast_runtime* rt, Rename_var** rename_var_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Rename_var* rename_var_v;
    unsigned long pos;

    rename_var_v = (Rename_var*)ast_alloc(rt,sizeof(Rename_var));
    if(rename_var_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Rename_var|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&rename_var_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&rename_var_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&rename_var_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(rename_var_vp) *rename_var_vp = rename_var_v;
done:
    return ACATCH(status);
} /*Rename_var_read*/

ast_err
Rename_var_reclaim(ast_runtime* rt, Rename_var* rename_var_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,rename_var_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)rename_var_v);
    goto done;

done:
    return ACATCH(status);

} /*Rename_var_reclaim*/

size_t
Rename_var_get_size(ast_runtime* rt, Rename_var* rename_var_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&rename_var_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&rename_var_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&rename_var_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Rename_var_get_size*/

ast_err
Rename_var_Return_write(ast_runtime* rt, Rename_var_Return* rename_var_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&rename_var_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Rename_var_Return_write*/

ast_err
Rename_var_Return_read(ast_runtime* rt, Rename_var_Return** rename_var_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Rename_var_Return* rename_var_return_v;
    unsigned long pos;

    rename_var_return_v = (Rename_var_Return*)ast_alloc(rt,sizeof(Rename_var_Return));
    if(rename_var_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Rename_var_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&rename_var_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(rename_var_return_vp) *rename_var_return_vp = rename_var_return_v;
done:
    return ACATCH(status);
} /*Rename_var_Return_read*/

ast_err
Rename_var_Return_reclaim(ast_runtime* rt, Rename_var_Return* rename_var_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)rename_var_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Rename_var_Return_reclaim*/

size_t
Rename_var_Return_get_size(ast_runtime* rt, Rename_var_Return* rename_var_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&rename_var_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Rename_var_Return_get_size*/

ast_err
Get_vara_write(ast_runtime* rt, Get_vara* get_vara_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_vara_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&get_vara_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<get_vara_v->start.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,3,&get_vara_v->start.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<get_vara_v->edges.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,4,&get_vara_v->edges.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_int32,5,&get_vara_v->memtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_vara_write*/

ast_err
Get_vara_read(ast_runtime* rt, Get_vara** get_vara_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_vara* get_vara_v;
    unsigned long pos;

    get_vara_v = (Get_vara*)ast_alloc(rt,sizeof(Get_vara));
    if(get_vara_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_vara|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_vara_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&get_vara_v->varid);
            } break;
        case 3: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_vara_v->start,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 4: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_vara_v->edges,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_int32,5,&get_vara_v->memtype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_vara_vp) *get_vara_vp = get_vara_v;
done:
    return ACATCH(status);
} /*Get_vara_read*/

ast_err
Get_vara_reclaim(ast_runtime* rt, Get_vara* get_vara_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)get_vara_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_vara_reclaim*/

size_t
Get_vara_get_size(ast_runtime* rt, Get_vara* get_vara_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_vara_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&get_vara_v->varid);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_vara_v->start.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_uint64,&get_vara_v->start.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_vara_v->edges.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_uint64,&get_vara_v->edges.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_int32,&get_vara_v->memtype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_vara_get_size*/

ast_err
Get_vara_Return_write(ast_runtime* rt, Get_vara_Return* get_vara_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_vara_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,2,&get_vara_return_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_vara_Return_write*/

ast_err
Get_vara_Return_read(ast_runtime* rt, Get_vara_Return** get_vara_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_vara_Return* get_vara_return_v;
    unsigned long pos;

    get_vara_return_v = (Get_vara_Return*)ast_alloc(rt,sizeof(Get_vara_Return));
    if(get_vara_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_vara_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_vara_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_bytes,2,&get_vara_return_v->value);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_vara_return_vp) *get_vara_return_vp = get_vara_return_v;
done:
    return ACATCH(status);
} /*Get_vara_Return_read*/

ast_err
Get_vara_Return_reclaim(ast_runtime* rt, Get_vara_Return* get_vara_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&get_vara_return_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)get_vara_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_vara_Return_reclaim*/

size_t
Get_vara_Return_get_size(ast_runtime* rt, Get_vara_Return* get_vara_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_vara_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_bytes,&get_vara_return_v->value);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_vara_Return_get_size*/

ast_err
Put_vara_write(ast_runtime* rt, Put_vara* put_vara_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_vara_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&put_vara_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<put_vara_v->start.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,3,&put_vara_v->start.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<put_vara_v->edges.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,4,&put_vara_v->edges.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_bytes,5,&put_vara_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,6,&put_vara_v->memtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_vara_write*/

ast_err
Put_vara_read(ast_runtime* rt, Put_vara** put_vara_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_vara* put_vara_v;
    unsigned long pos;

    put_vara_v = (Put_vara*)ast_alloc(rt,sizeof(Put_vara));
    if(put_vara_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_vara|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_vara_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&put_vara_v->varid);
            } break;
        case 3: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_vara_v->start,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 4: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_vara_v->edges,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_bytes,5,&put_vara_v->value);
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_int32,6,&put_vara_v->memtype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_vara_vp) *put_vara_vp = put_vara_v;
done:
    return ACATCH(status);
} /*Put_vara_read*/

ast_err
Put_vara_reclaim(ast_runtime* rt, Put_vara* put_vara_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&put_vara_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)put_vara_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_vara_reclaim*/

size_t
Put_vara_get_size(ast_runtime* rt, Put_vara* put_vara_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_vara_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&put_vara_v->varid);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_vara_v->start.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_uint64,&put_vara_v->start.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_vara_v->edges.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_uint64,&put_vara_v->edges.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_bytes,&put_vara_v->value);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_int32,&put_vara_v->memtype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_vara_get_size*/

ast_err
Put_vara_Return_write(ast_runtime* rt, Put_vara_Return* put_vara_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_vara_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_vara_Return_write*/

ast_err
Put_vara_Return_read(ast_runtime* rt, Put_vara_Return** put_vara_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_vara_Return* put_vara_return_v;
    unsigned long pos;

    put_vara_return_v = (Put_vara_Return*)ast_alloc(rt,sizeof(Put_vara_Return));
    if(put_vara_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_vara_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_vara_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_vara_return_vp) *put_vara_return_vp = put_vara_return_v;
done:
    return ACATCH(status);
} /*Put_vara_Return_read*/

ast_err
Put_vara_Return_reclaim(ast_runtime* rt, Put_vara_Return* put_vara_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)put_vara_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_vara_Return_reclaim*/

size_t
Put_vara_Return_get_size(ast_runtime* rt, Put_vara_Return* put_vara_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_vara_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_vara_Return_get_size*/

ast_err
Get_vars_write(ast_runtime* rt, Get_vars* get_vars_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_vars_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&get_vars_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<get_vars_v->start.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,3,&get_vars_v->start.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<get_vars_v->edges.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,4,&get_vars_v->edges.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<get_vars_v->stride.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,5,&get_vars_v->stride.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_int32,6,&get_vars_v->memtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_vars_write*/

ast_err
Get_vars_read(ast_runtime* rt, Get_vars** get_vars_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_vars* get_vars_v;
    unsigned long pos;

    get_vars_v = (Get_vars*)ast_alloc(rt,sizeof(Get_vars));
    if(get_vars_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_vars|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_vars_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&get_vars_v->varid);
            } break;
        case 3: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_vars_v->start,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 4: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_vars_v->edges,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 5: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,5,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_vars_v->stride,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_int32,6,&get_vars_v->memtype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_vars_vp) *get_vars_vp = get_vars_v;
done:
    return ACATCH(status);
} /*Get_vars_read*/

ast_err
Get_vars_reclaim(ast_runtime* rt, Get_vars* get_vars_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)get_vars_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_vars_reclaim*/

size_t
Get_vars_get_size(ast_runtime* rt, Get_vars* get_vars_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_vars_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&get_vars_v->varid);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_vars_v->start.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_uint64,&get_vars_v->start.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_vars_v->edges.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_uint64,&get_vars_v->edges.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_vars_v->stride.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,5);
            fieldsize += ast_get_size(rt,ast_uint64,&get_vars_v->stride.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_int32,&get_vars_v->memtype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_vars_get_size*/

ast_err
Get_vars_Return_write(ast_runtime* rt, Get_vars_Return* get_vars_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_vars_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,2,&get_vars_return_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_vars_Return_write*/

ast_err
Get_vars_Return_read(ast_runtime* rt, Get_vars_Return** get_vars_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_vars_Return* get_vars_return_v;
    unsigned long pos;

    get_vars_return_v = (Get_vars_Return*)ast_alloc(rt,sizeof(Get_vars_Return));
    if(get_vars_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_vars_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_vars_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_bytes,2,&get_vars_return_v->value);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_vars_return_vp) *get_vars_return_vp = get_vars_return_v;
done:
    return ACATCH(status);
} /*Get_vars_Return_read*/

ast_err
Get_vars_Return_reclaim(ast_runtime* rt, Get_vars_Return* get_vars_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&get_vars_return_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)get_vars_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_vars_Return_reclaim*/

size_t
Get_vars_Return_get_size(ast_runtime* rt, Get_vars_Return* get_vars_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_vars_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_bytes,&get_vars_return_v->value);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_vars_Return_get_size*/

ast_err
Put_vars_write(ast_runtime* rt, Put_vars* put_vars_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_vars_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&put_vars_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<put_vars_v->start.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,3,&put_vars_v->start.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<put_vars_v->edges.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,4,&put_vars_v->edges.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<put_vars_v->stride.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,5,&put_vars_v->stride.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_bytes,6,&put_vars_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,7,&put_vars_v->memtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_vars_write*/

ast_err
Put_vars_read(ast_runtime* rt, Put_vars** put_vars_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_vars* put_vars_v;
    unsigned long pos;

    put_vars_v = (Put_vars*)ast_alloc(rt,sizeof(Put_vars));
    if(put_vars_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_vars|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_vars_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&put_vars_v->varid);
            } break;
        case 3: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_vars_v->start,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 4: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_vars_v->edges,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 5: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,5,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_vars_v->stride,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_bytes,6,&put_vars_v->value);
            } break;
        case 7: {
            status = ast_read_primitive(rt,ast_int32,7,&put_vars_v->memtype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_vars_vp) *put_vars_vp = put_vars_v;
done:
    return ACATCH(status);
} /*Put_vars_read*/

ast_err
Put_vars_reclaim(ast_runtime* rt, Put_vars* put_vars_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&put_vars_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)put_vars_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_vars_reclaim*/

size_t
Put_vars_get_size(ast_runtime* rt, Put_vars* put_vars_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_vars_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&put_vars_v->varid);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_vars_v->start.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_uint64,&put_vars_v->start.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_vars_v->edges.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_uint64,&put_vars_v->edges.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_vars_v->stride.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,5);
            fieldsize += ast_get_size(rt,ast_uint64,&put_vars_v->stride.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_bytes,&put_vars_v->value);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,7);
        fieldsize += ast_get_size(rt,ast_int32,&put_vars_v->memtype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_vars_get_size*/

ast_err
Put_vars_Return_write(ast_runtime* rt, Put_vars_Return* put_vars_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_vars_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_vars_Return_write*/

ast_err
Put_vars_Return_read(ast_runtime* rt, Put_vars_Return** put_vars_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_vars_Return* put_vars_return_v;
    unsigned long pos;

    put_vars_return_v = (Put_vars_Return*)ast_alloc(rt,sizeof(Put_vars_Return));
    if(put_vars_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_vars_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_vars_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_vars_return_vp) *put_vars_return_vp = put_vars_return_v;
done:
    return ACATCH(status);
} /*Put_vars_Return_read*/

ast_err
Put_vars_Return_reclaim(ast_runtime* rt, Put_vars_Return* put_vars_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)put_vars_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_vars_Return_reclaim*/

size_t
Put_vars_Return_get_size(ast_runtime* rt, Put_vars_Return* put_vars_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_vars_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_vars_Return_get_size*/

ast_err
Get_varm_write(ast_runtime* rt, Get_varm* get_varm_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_varm_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&get_varm_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<get_varm_v->start.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,3,&get_varm_v->start.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<get_varm_v->edges.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,4,&get_varm_v->edges.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<get_varm_v->stride.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,5,&get_varm_v->stride.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<get_varm_v->imap.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,6,&get_varm_v->imap.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_int32,7,&get_varm_v->memtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_varm_write*/

ast_err
Get_varm_read(ast_runtime* rt, Get_varm** get_varm_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_varm* get_varm_v;
    unsigned long pos;

    get_varm_v = (Get_varm*)ast_alloc(rt,sizeof(Get_varm));
    if(get_varm_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_varm|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_varm_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&get_varm_v->varid);
            } break;
        case 3: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_varm_v->start,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 4: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_varm_v->edges,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 5: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,5,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_varm_v->stride,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 6: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,6,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&get_varm_v->imap,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 7: {
            status = ast_read_primitive(rt,ast_int32,7,&get_varm_v->memtype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_varm_vp) *get_varm_vp = get_varm_v;
done:
    return ACATCH(status);
} /*Get_varm_read*/

ast_err
Get_varm_reclaim(ast_runtime* rt, Get_varm* get_varm_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)get_varm_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_varm_reclaim*/

size_t
Get_varm_get_size(ast_runtime* rt, Get_varm* get_varm_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_varm_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&get_varm_v->varid);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_varm_v->start.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_uint64,&get_varm_v->start.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_varm_v->edges.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_uint64,&get_varm_v->edges.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_varm_v->stride.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,5);
            fieldsize += ast_get_size(rt,ast_uint64,&get_varm_v->stride.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<get_varm_v->imap.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,6);
            fieldsize += ast_get_size(rt,ast_uint64,&get_varm_v->imap.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,7);
        fieldsize += ast_get_size(rt,ast_int32,&get_varm_v->memtype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_varm_get_size*/

ast_err
Get_varm_Return_write(ast_runtime* rt, Get_varm_Return* get_varm_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_varm_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,2,&get_varm_return_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_varm_Return_write*/

ast_err
Get_varm_Return_read(ast_runtime* rt, Get_varm_Return** get_varm_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_varm_Return* get_varm_return_v;
    unsigned long pos;

    get_varm_return_v = (Get_varm_Return*)ast_alloc(rt,sizeof(Get_varm_Return));
    if(get_varm_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_varm_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_varm_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_bytes,2,&get_varm_return_v->value);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_varm_return_vp) *get_varm_return_vp = get_varm_return_v;
done:
    return ACATCH(status);
} /*Get_varm_Return_read*/

ast_err
Get_varm_Return_reclaim(ast_runtime* rt, Get_varm_Return* get_varm_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&get_varm_return_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)get_varm_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_varm_Return_reclaim*/

size_t
Get_varm_Return_get_size(ast_runtime* rt, Get_varm_Return* get_varm_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_varm_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_bytes,&get_varm_return_v->value);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_varm_Return_get_size*/

ast_err
Put_varm_write(ast_runtime* rt, Put_varm* put_varm_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_varm_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&put_varm_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<put_varm_v->start.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,3,&put_varm_v->start.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<put_varm_v->edges.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,4,&put_varm_v->edges.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<put_varm_v->stride.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,5,&put_varm_v->stride.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        int i = 0;
        for(i=0;i<put_varm_v->imap.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,6,&put_varm_v->imap.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_bytes,7,&put_varm_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,8,&put_varm_v->memtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_varm_write*/

ast_err
Put_varm_read(ast_runtime* rt, Put_varm** put_varm_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_varm* put_varm_v;
    unsigned long pos;

    put_varm_v = (Put_varm*)ast_alloc(rt,sizeof(Put_varm));
    if(put_varm_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_varm|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_varm_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&put_varm_v->varid);
            } break;
        case 3: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_varm_v->start,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 4: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_varm_v->edges,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 5: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,5,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_varm_v->stride,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 6: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,6,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&put_varm_v->imap,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 7: {
            status = ast_read_primitive(rt,ast_bytes,7,&put_varm_v->value);
            } break;
        case 8: {
            status = ast_read_primitive(rt,ast_int32,8,&put_varm_v->memtype);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_varm_vp) *put_varm_vp = put_varm_v;
done:
    return ACATCH(status);
} /*Put_varm_read*/

ast_err
Put_varm_reclaim(ast_runtime* rt, Put_varm* put_varm_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&put_varm_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)put_varm_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_varm_reclaim*/

size_t
Put_varm_get_size(ast_runtime* rt, Put_varm* put_varm_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_varm_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&put_varm_v->varid);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_varm_v->start.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_uint64,&put_varm_v->start.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_varm_v->edges.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_uint64,&put_varm_v->edges.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_varm_v->stride.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,5);
            fieldsize += ast_get_size(rt,ast_uint64,&put_varm_v->stride.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<put_varm_v->imap.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,6);
            fieldsize += ast_get_size(rt,ast_uint64,&put_varm_v->imap.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,7);
        fieldsize += ast_get_size(rt,ast_bytes,&put_varm_v->value);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,8);
        fieldsize += ast_get_size(rt,ast_int32,&put_varm_v->memtype);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_varm_get_size*/

ast_err
Put_varm_Return_write(ast_runtime* rt, Put_varm_Return* put_varm_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_varm_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_varm_Return_write*/

ast_err
Put_varm_Return_read(ast_runtime* rt, Put_varm_Return** put_varm_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_varm_Return* put_varm_return_v;
    unsigned long pos;

    put_varm_return_v = (Put_varm_Return*)ast_alloc(rt,sizeof(Put_varm_Return));
    if(put_varm_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_varm_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_varm_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_varm_return_vp) *put_varm_return_vp = put_varm_return_v;
done:
    return ACATCH(status);
} /*Put_varm_Return_read*/

ast_err
Put_varm_Return_reclaim(ast_runtime* rt, Put_varm_Return* put_varm_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)put_varm_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_varm_Return_reclaim*/

size_t
Put_varm_Return_get_size(ast_runtime* rt, Put_varm_Return* put_varm_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_varm_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_varm_Return_get_size*/

ast_err
Inq_var_all_write(ast_runtime* rt, Inq_var_all* inq_var_all_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_var_all_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_var_all_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&inq_var_all_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_var_all_write*/

ast_err
Inq_var_all_read(ast_runtime* rt, Inq_var_all** inq_var_all_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_var_all* inq_var_all_v;
    unsigned long pos;

    inq_var_all_v = (Inq_var_all*)ast_alloc(rt,sizeof(Inq_var_all));
    if(inq_var_all_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_var_all|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_var_all_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_var_all_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&inq_var_all_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_var_all_vp) *inq_var_all_vp = inq_var_all_v;
done:
    return ACATCH(status);
} /*Inq_var_all_read*/

ast_err
Inq_var_all_reclaim(ast_runtime* rt, Inq_var_all* inq_var_all_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_var_all_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_var_all_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_var_all_reclaim*/

size_t
Inq_var_all_get_size(ast_runtime* rt, Inq_var_all* inq_var_all_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&inq_var_all_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_var_all_get_size*/

ast_err
Inq_var_all_Return_write(ast_runtime* rt, Inq_var_all_Return* inq_var_all_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_var_all_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_var_all_return_v->xtype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&inq_var_all_return_v->ndims);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_var_all_return_v->dimids.count;i++) {
            status = ast_write_primitive(rt,ast_int32,4,&inq_var_all_return_v->dimids.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_int32,5,&inq_var_all_return_v->natts);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,6,&inq_var_all_return_v->shuffle);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,7,&inq_var_all_return_v->deflate);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,8,&inq_var_all_return_v->deflate_level);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,9,&inq_var_all_return_v->fletcher32);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,10,&inq_var_all_return_v->contiguous);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_var_all_return_v->chunksizes.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,11,&inq_var_all_return_v->chunksizes.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_bool,12,&inq_var_all_return_v->no_fill);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,13,&inq_var_all_return_v->fill_value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,14,&inq_var_all_return_v->endianness);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,15,&inq_var_all_return_v->options_mask);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,16,&inq_var_all_return_v->pixels_per_block);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_var_all_Return_write*/

ast_err
Inq_var_all_Return_read(ast_runtime* rt, Inq_var_all_Return** inq_var_all_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_var_all_Return* inq_var_all_return_v;
    unsigned long pos;

    inq_var_all_return_v = (Inq_var_all_Return*)ast_alloc(rt,sizeof(Inq_var_all_Return));
    if(inq_var_all_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_var_all_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_var_all_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_var_all_return_v->xtype);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&inq_var_all_return_v->ndims);
            } break;
        case 4: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&inq_var_all_return_v->dimids,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_int32,5,&inq_var_all_return_v->natts);
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_bool,6,&inq_var_all_return_v->shuffle);
            } break;
        case 7: {
            status = ast_read_primitive(rt,ast_bool,7,&inq_var_all_return_v->deflate);
            } break;
        case 8: {
            status = ast_read_primitive(rt,ast_int32,8,&inq_var_all_return_v->deflate_level);
            } break;
        case 9: {
            status = ast_read_primitive(rt,ast_bool,9,&inq_var_all_return_v->fletcher32);
            } break;
        case 10: {
            status = ast_read_primitive(rt,ast_bool,10,&inq_var_all_return_v->contiguous);
            } break;
        case 11: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,11,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&inq_var_all_return_v->chunksizes,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 12: {
            status = ast_read_primitive(rt,ast_bool,12,&inq_var_all_return_v->no_fill);
            } break;
        case 13: {
            status = ast_read_primitive(rt,ast_bytes,13,&inq_var_all_return_v->fill_value);
            } break;
        case 14: {
            status = ast_read_primitive(rt,ast_bool,14,&inq_var_all_return_v->endianness);
            } break;
        case 15: {
            status = ast_read_primitive(rt,ast_int32,15,&inq_var_all_return_v->options_mask);
            } break;
        case 16: {
            status = ast_read_primitive(rt,ast_int32,16,&inq_var_all_return_v->pixels_per_block);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_var_all_return_vp) *inq_var_all_return_vp = inq_var_all_return_v;
done:
    return ACATCH(status);
} /*Inq_var_all_Return_read*/

ast_err
Inq_var_all_Return_reclaim(ast_runtime* rt, Inq_var_all_Return* inq_var_all_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&inq_var_all_return_v->fill_value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_var_all_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_var_all_Return_reclaim*/

size_t
Inq_var_all_Return_get_size(ast_runtime* rt, Inq_var_all_Return* inq_var_all_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_return_v->xtype);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_return_v->ndims);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_var_all_return_v->dimids.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_return_v->dimids.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_return_v->natts);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_bool,&inq_var_all_return_v->shuffle);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,7);
        fieldsize += ast_get_size(rt,ast_bool,&inq_var_all_return_v->deflate);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,8);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_return_v->deflate_level);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,9);
        fieldsize += ast_get_size(rt,ast_bool,&inq_var_all_return_v->fletcher32);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,10);
        fieldsize += ast_get_size(rt,ast_bool,&inq_var_all_return_v->contiguous);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_var_all_return_v->chunksizes.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,11);
            fieldsize += ast_get_size(rt,ast_uint64,&inq_var_all_return_v->chunksizes.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,12);
        fieldsize += ast_get_size(rt,ast_bool,&inq_var_all_return_v->no_fill);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,13);
        fieldsize += ast_get_size(rt,ast_bytes,&inq_var_all_return_v->fill_value);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,14);
        fieldsize += ast_get_size(rt,ast_bool,&inq_var_all_return_v->endianness);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,15);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_return_v->options_mask);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,16);
        fieldsize += ast_get_size(rt,ast_int32,&inq_var_all_return_v->pixels_per_block);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_var_all_Return_get_size*/

ast_err
Show_metadata_write(ast_runtime* rt, Show_metadata* show_metadata_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&show_metadata_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Show_metadata_write*/

ast_err
Show_metadata_read(ast_runtime* rt, Show_metadata** show_metadata_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Show_metadata* show_metadata_v;
    unsigned long pos;

    show_metadata_v = (Show_metadata*)ast_alloc(rt,sizeof(Show_metadata));
    if(show_metadata_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Show_metadata|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&show_metadata_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(show_metadata_vp) *show_metadata_vp = show_metadata_v;
done:
    return ACATCH(status);
} /*Show_metadata_read*/

ast_err
Show_metadata_reclaim(ast_runtime* rt, Show_metadata* show_metadata_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)show_metadata_v);
    goto done;

done:
    return ACATCH(status);

} /*Show_metadata_reclaim*/

size_t
Show_metadata_get_size(ast_runtime* rt, Show_metadata* show_metadata_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&show_metadata_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Show_metadata_get_size*/

ast_err
Show_metadata_Return_write(ast_runtime* rt, Show_metadata_Return* show_metadata_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&show_metadata_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Show_metadata_Return_write*/

ast_err
Show_metadata_Return_read(ast_runtime* rt, Show_metadata_Return** show_metadata_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Show_metadata_Return* show_metadata_return_v;
    unsigned long pos;

    show_metadata_return_v = (Show_metadata_Return*)ast_alloc(rt,sizeof(Show_metadata_Return));
    if(show_metadata_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Show_metadata_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&show_metadata_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(show_metadata_return_vp) *show_metadata_return_vp = show_metadata_return_v;
done:
    return ACATCH(status);
} /*Show_metadata_Return_read*/

ast_err
Show_metadata_Return_reclaim(ast_runtime* rt, Show_metadata_Return* show_metadata_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)show_metadata_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Show_metadata_Return_reclaim*/

size_t
Show_metadata_Return_get_size(ast_runtime* rt, Show_metadata_Return* show_metadata_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&show_metadata_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Show_metadata_Return_get_size*/

ast_err
Inq_unlimdims_write(ast_runtime* rt, Inq_unlimdims* inq_unlimdims_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_unlimdims_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_unlimdims_write*/

ast_err
Inq_unlimdims_read(ast_runtime* rt, Inq_unlimdims** inq_unlimdims_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_unlimdims* inq_unlimdims_v;
    unsigned long pos;

    inq_unlimdims_v = (Inq_unlimdims*)ast_alloc(rt,sizeof(Inq_unlimdims));
    if(inq_unlimdims_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_unlimdims|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_unlimdims_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_unlimdims_vp) *inq_unlimdims_vp = inq_unlimdims_v;
done:
    return ACATCH(status);
} /*Inq_unlimdims_read*/

ast_err
Inq_unlimdims_reclaim(ast_runtime* rt, Inq_unlimdims* inq_unlimdims_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_unlimdims_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_unlimdims_reclaim*/

size_t
Inq_unlimdims_get_size(ast_runtime* rt, Inq_unlimdims* inq_unlimdims_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_unlimdims_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_unlimdims_get_size*/

ast_err
Inq_unlimdims_Return_write(ast_runtime* rt, Inq_unlimdims_Return* inq_unlimdims_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_unlimdims_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_unlimdims_return_v->nunlimdims);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_unlimdims_return_v->unlimdimids.count;i++) {
            status = ast_write_primitive(rt,ast_int32,3,&inq_unlimdims_return_v->unlimdimids.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Inq_unlimdims_Return_write*/

ast_err
Inq_unlimdims_Return_read(ast_runtime* rt, Inq_unlimdims_Return** inq_unlimdims_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_unlimdims_Return* inq_unlimdims_return_v;
    unsigned long pos;

    inq_unlimdims_return_v = (Inq_unlimdims_Return*)ast_alloc(rt,sizeof(Inq_unlimdims_Return));
    if(inq_unlimdims_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_unlimdims_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_unlimdims_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_unlimdims_return_v->nunlimdims);
            } break;
        case 3: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&inq_unlimdims_return_v->unlimdimids,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_unlimdims_return_vp) *inq_unlimdims_return_vp = inq_unlimdims_return_v;
done:
    return ACATCH(status);
} /*Inq_unlimdims_Return_read*/

ast_err
Inq_unlimdims_Return_reclaim(ast_runtime* rt, Inq_unlimdims_Return* inq_unlimdims_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_unlimdims_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_unlimdims_Return_reclaim*/

size_t
Inq_unlimdims_Return_get_size(ast_runtime* rt, Inq_unlimdims_Return* inq_unlimdims_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_unlimdims_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_unlimdims_return_v->nunlimdims);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_unlimdims_return_v->unlimdimids.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_int32,&inq_unlimdims_return_v->unlimdimids.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_unlimdims_Return_get_size*/

ast_err
Var_par_access_write(ast_runtime* rt, Var_par_access* var_par_access_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&var_par_access_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&var_par_access_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,3,&var_par_access_v->par_access);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Var_par_access_write*/

ast_err
Var_par_access_read(ast_runtime* rt, Var_par_access** var_par_access_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Var_par_access* var_par_access_v;
    unsigned long pos;

    var_par_access_v = (Var_par_access*)ast_alloc(rt,sizeof(Var_par_access));
    if(var_par_access_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Var_par_access|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&var_par_access_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&var_par_access_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_bool,3,&var_par_access_v->par_access);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(var_par_access_vp) *var_par_access_vp = var_par_access_v;
done:
    return ACATCH(status);
} /*Var_par_access_read*/

ast_err
Var_par_access_reclaim(ast_runtime* rt, Var_par_access* var_par_access_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)var_par_access_v);
    goto done;

done:
    return ACATCH(status);

} /*Var_par_access_reclaim*/

size_t
Var_par_access_get_size(ast_runtime* rt, Var_par_access* var_par_access_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&var_par_access_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&var_par_access_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_bool,&var_par_access_v->par_access);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Var_par_access_get_size*/

ast_err
Var_par_access_Return_write(ast_runtime* rt, Var_par_access_Return* var_par_access_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&var_par_access_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Var_par_access_Return_write*/

ast_err
Var_par_access_Return_read(ast_runtime* rt, Var_par_access_Return** var_par_access_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Var_par_access_Return* var_par_access_return_v;
    unsigned long pos;

    var_par_access_return_v = (Var_par_access_Return*)ast_alloc(rt,sizeof(Var_par_access_Return));
    if(var_par_access_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Var_par_access_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&var_par_access_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(var_par_access_return_vp) *var_par_access_return_vp = var_par_access_return_v;
done:
    return ACATCH(status);
} /*Var_par_access_Return_read*/

ast_err
Var_par_access_Return_reclaim(ast_runtime* rt, Var_par_access_Return* var_par_access_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)var_par_access_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Var_par_access_Return_reclaim*/

size_t
Var_par_access_Return_get_size(ast_runtime* rt, Var_par_access_Return* var_par_access_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&var_par_access_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Var_par_access_Return_get_size*/

ast_err
Inq_ncid_write(ast_runtime* rt, Inq_ncid* inq_ncid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_ncid_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_ncid_v->group);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_ncid_write*/

ast_err
Inq_ncid_read(ast_runtime* rt, Inq_ncid** inq_ncid_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_ncid* inq_ncid_v;
    unsigned long pos;

    inq_ncid_v = (Inq_ncid*)ast_alloc(rt,sizeof(Inq_ncid));
    if(inq_ncid_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_ncid|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_ncid_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_ncid_v->group);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_ncid_vp) *inq_ncid_vp = inq_ncid_v;
done:
    return ACATCH(status);
} /*Inq_ncid_read*/

ast_err
Inq_ncid_reclaim(ast_runtime* rt, Inq_ncid* inq_ncid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_ncid_v->group);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_ncid_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_ncid_reclaim*/

size_t
Inq_ncid_get_size(ast_runtime* rt, Inq_ncid* inq_ncid_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_ncid_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_ncid_v->group);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_ncid_get_size*/

ast_err
Inq_ncid_Return_write(ast_runtime* rt, Inq_ncid_Return* inq_ncid_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_ncid_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_ncid_return_v->grp_ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_ncid_Return_write*/

ast_err
Inq_ncid_Return_read(ast_runtime* rt, Inq_ncid_Return** inq_ncid_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_ncid_Return* inq_ncid_return_v;
    unsigned long pos;

    inq_ncid_return_v = (Inq_ncid_Return*)ast_alloc(rt,sizeof(Inq_ncid_Return));
    if(inq_ncid_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_ncid_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_ncid_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_ncid_return_v->grp_ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_ncid_return_vp) *inq_ncid_return_vp = inq_ncid_return_v;
done:
    return ACATCH(status);
} /*Inq_ncid_Return_read*/

ast_err
Inq_ncid_Return_reclaim(ast_runtime* rt, Inq_ncid_Return* inq_ncid_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_ncid_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_ncid_Return_reclaim*/

size_t
Inq_ncid_Return_get_size(ast_runtime* rt, Inq_ncid_Return* inq_ncid_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_ncid_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_ncid_return_v->grp_ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_ncid_Return_get_size*/

ast_err
Inq_grps_write(ast_runtime* rt, Inq_grps* inq_grps_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grps_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grps_write*/

ast_err
Inq_grps_read(ast_runtime* rt, Inq_grps** inq_grps_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grps* inq_grps_v;
    unsigned long pos;

    inq_grps_v = (Inq_grps*)ast_alloc(rt,sizeof(Inq_grps));
    if(inq_grps_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grps|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grps_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grps_vp) *inq_grps_vp = inq_grps_v;
done:
    return ACATCH(status);
} /*Inq_grps_read*/

ast_err
Inq_grps_reclaim(ast_runtime* rt, Inq_grps* inq_grps_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_grps_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grps_reclaim*/

size_t
Inq_grps_get_size(ast_runtime* rt, Inq_grps* inq_grps_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grps_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grps_get_size*/

ast_err
Inq_grps_Return_write(ast_runtime* rt, Inq_grps_Return* inq_grps_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grps_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_grps_return_v->ngroups);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_grps_return_v->ncids.count;i++) {
            status = ast_write_primitive(rt,ast_int32,3,&inq_grps_return_v->ncids.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Inq_grps_Return_write*/

ast_err
Inq_grps_Return_read(ast_runtime* rt, Inq_grps_Return** inq_grps_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grps_Return* inq_grps_return_v;
    unsigned long pos;

    inq_grps_return_v = (Inq_grps_Return*)ast_alloc(rt,sizeof(Inq_grps_Return));
    if(inq_grps_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grps_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grps_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_grps_return_v->ngroups);
            } break;
        case 3: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&inq_grps_return_v->ncids,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grps_return_vp) *inq_grps_return_vp = inq_grps_return_v;
done:
    return ACATCH(status);
} /*Inq_grps_Return_read*/

ast_err
Inq_grps_Return_reclaim(ast_runtime* rt, Inq_grps_Return* inq_grps_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_grps_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grps_Return_reclaim*/

size_t
Inq_grps_Return_get_size(ast_runtime* rt, Inq_grps_Return* inq_grps_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grps_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grps_return_v->ngroups);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_grps_return_v->ncids.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_int32,&inq_grps_return_v->ncids.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grps_Return_get_size*/

ast_err
Inq_grpname_write(ast_runtime* rt, Inq_grpname* inq_grpname_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grpname_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grpname_write*/

ast_err
Inq_grpname_read(ast_runtime* rt, Inq_grpname** inq_grpname_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grpname* inq_grpname_v;
    unsigned long pos;

    inq_grpname_v = (Inq_grpname*)ast_alloc(rt,sizeof(Inq_grpname));
    if(inq_grpname_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grpname|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grpname_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grpname_vp) *inq_grpname_vp = inq_grpname_v;
done:
    return ACATCH(status);
} /*Inq_grpname_read*/

ast_err
Inq_grpname_reclaim(ast_runtime* rt, Inq_grpname* inq_grpname_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_grpname_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grpname_reclaim*/

size_t
Inq_grpname_get_size(ast_runtime* rt, Inq_grpname* inq_grpname_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grpname_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grpname_get_size*/

ast_err
Inq_grpname_Return_write(ast_runtime* rt, Inq_grpname_Return* inq_grpname_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grpname_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_grpname_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grpname_Return_write*/

ast_err
Inq_grpname_Return_read(ast_runtime* rt, Inq_grpname_Return** inq_grpname_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grpname_Return* inq_grpname_return_v;
    unsigned long pos;

    inq_grpname_return_v = (Inq_grpname_Return*)ast_alloc(rt,sizeof(Inq_grpname_Return));
    if(inq_grpname_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grpname_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grpname_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_grpname_return_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grpname_return_vp) *inq_grpname_return_vp = inq_grpname_return_v;
done:
    return ACATCH(status);
} /*Inq_grpname_Return_read*/

ast_err
Inq_grpname_Return_reclaim(ast_runtime* rt, Inq_grpname_Return* inq_grpname_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_grpname_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_grpname_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grpname_Return_reclaim*/

size_t
Inq_grpname_Return_get_size(ast_runtime* rt, Inq_grpname_Return* inq_grpname_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grpname_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_grpname_return_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grpname_Return_get_size*/

ast_err
Inq_grpname_full_write(ast_runtime* rt, Inq_grpname_full* inq_grpname_full_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grpname_full_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grpname_full_write*/

ast_err
Inq_grpname_full_read(ast_runtime* rt, Inq_grpname_full** inq_grpname_full_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grpname_full* inq_grpname_full_v;
    unsigned long pos;

    inq_grpname_full_v = (Inq_grpname_full*)ast_alloc(rt,sizeof(Inq_grpname_full));
    if(inq_grpname_full_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grpname_full|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grpname_full_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grpname_full_vp) *inq_grpname_full_vp = inq_grpname_full_v;
done:
    return ACATCH(status);
} /*Inq_grpname_full_read*/

ast_err
Inq_grpname_full_reclaim(ast_runtime* rt, Inq_grpname_full* inq_grpname_full_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_grpname_full_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grpname_full_reclaim*/

size_t
Inq_grpname_full_get_size(ast_runtime* rt, Inq_grpname_full* inq_grpname_full_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grpname_full_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grpname_full_get_size*/

ast_err
Inq_grpname_full_Return_write(ast_runtime* rt, Inq_grpname_full_Return* inq_grpname_full_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grpname_full_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_grpname_full_return_v->len.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,2,&inq_grpname_full_return_v->len.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&inq_grpname_full_return_v->fullname);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grpname_full_Return_write*/

ast_err
Inq_grpname_full_Return_read(ast_runtime* rt, Inq_grpname_full_Return** inq_grpname_full_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grpname_full_Return* inq_grpname_full_return_v;
    unsigned long pos;

    inq_grpname_full_return_v = (Inq_grpname_full_Return*)ast_alloc(rt,sizeof(Inq_grpname_full_Return));
    if(inq_grpname_full_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grpname_full_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grpname_full_return_v->ncstatus);
            } break;
        case 2: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,2,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&inq_grpname_full_return_v->len,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&inq_grpname_full_return_v->fullname);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grpname_full_return_vp) *inq_grpname_full_return_vp = inq_grpname_full_return_v;
done:
    return ACATCH(status);
} /*Inq_grpname_full_Return_read*/

ast_err
Inq_grpname_full_Return_reclaim(ast_runtime* rt, Inq_grpname_full_Return* inq_grpname_full_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_grpname_full_return_v->fullname);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_grpname_full_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grpname_full_Return_reclaim*/

size_t
Inq_grpname_full_Return_get_size(ast_runtime* rt, Inq_grpname_full_Return* inq_grpname_full_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grpname_full_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_grpname_full_return_v->len.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,2);
            fieldsize += ast_get_size(rt,ast_uint64,&inq_grpname_full_return_v->len.values[i]);
        }
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&inq_grpname_full_return_v->fullname);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grpname_full_Return_get_size*/

ast_err
Inq_grp_parent_write(ast_runtime* rt, Inq_grp_parent* inq_grp_parent_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grp_parent_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grp_parent_write*/

ast_err
Inq_grp_parent_read(ast_runtime* rt, Inq_grp_parent** inq_grp_parent_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grp_parent* inq_grp_parent_v;
    unsigned long pos;

    inq_grp_parent_v = (Inq_grp_parent*)ast_alloc(rt,sizeof(Inq_grp_parent));
    if(inq_grp_parent_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grp_parent|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grp_parent_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grp_parent_vp) *inq_grp_parent_vp = inq_grp_parent_v;
done:
    return ACATCH(status);
} /*Inq_grp_parent_read*/

ast_err
Inq_grp_parent_reclaim(ast_runtime* rt, Inq_grp_parent* inq_grp_parent_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_grp_parent_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grp_parent_reclaim*/

size_t
Inq_grp_parent_get_size(ast_runtime* rt, Inq_grp_parent* inq_grp_parent_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grp_parent_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grp_parent_get_size*/

ast_err
Inq_grp_parent_Return_write(ast_runtime* rt, Inq_grp_parent_Return* inq_grp_parent_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grp_parent_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_grp_parent_return_v->parentncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grp_parent_Return_write*/

ast_err
Inq_grp_parent_Return_read(ast_runtime* rt, Inq_grp_parent_Return** inq_grp_parent_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grp_parent_Return* inq_grp_parent_return_v;
    unsigned long pos;

    inq_grp_parent_return_v = (Inq_grp_parent_Return*)ast_alloc(rt,sizeof(Inq_grp_parent_Return));
    if(inq_grp_parent_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grp_parent_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grp_parent_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_grp_parent_return_v->parentncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grp_parent_return_vp) *inq_grp_parent_return_vp = inq_grp_parent_return_v;
done:
    return ACATCH(status);
} /*Inq_grp_parent_Return_read*/

ast_err
Inq_grp_parent_Return_reclaim(ast_runtime* rt, Inq_grp_parent_Return* inq_grp_parent_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_grp_parent_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grp_parent_Return_reclaim*/

size_t
Inq_grp_parent_Return_get_size(ast_runtime* rt, Inq_grp_parent_Return* inq_grp_parent_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grp_parent_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grp_parent_return_v->parentncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grp_parent_Return_get_size*/

ast_err
Inq_grp_full_ncid_write(ast_runtime* rt, Inq_grp_full_ncid* inq_grp_full_ncid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grp_full_ncid_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_grp_full_ncid_v->fullname);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grp_full_ncid_write*/

ast_err
Inq_grp_full_ncid_read(ast_runtime* rt, Inq_grp_full_ncid** inq_grp_full_ncid_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grp_full_ncid* inq_grp_full_ncid_v;
    unsigned long pos;

    inq_grp_full_ncid_v = (Inq_grp_full_ncid*)ast_alloc(rt,sizeof(Inq_grp_full_ncid));
    if(inq_grp_full_ncid_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grp_full_ncid|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grp_full_ncid_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_grp_full_ncid_v->fullname);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grp_full_ncid_vp) *inq_grp_full_ncid_vp = inq_grp_full_ncid_v;
done:
    return ACATCH(status);
} /*Inq_grp_full_ncid_read*/

ast_err
Inq_grp_full_ncid_reclaim(ast_runtime* rt, Inq_grp_full_ncid* inq_grp_full_ncid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_grp_full_ncid_v->fullname);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_grp_full_ncid_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grp_full_ncid_reclaim*/

size_t
Inq_grp_full_ncid_get_size(ast_runtime* rt, Inq_grp_full_ncid* inq_grp_full_ncid_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grp_full_ncid_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_grp_full_ncid_v->fullname);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grp_full_ncid_get_size*/

ast_err
Inq_grp_full_ncid_Return_write(ast_runtime* rt, Inq_grp_full_ncid_Return* inq_grp_full_ncid_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_grp_full_ncid_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_grp_full_ncid_return_v->groupncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_grp_full_ncid_Return_write*/

ast_err
Inq_grp_full_ncid_Return_read(ast_runtime* rt, Inq_grp_full_ncid_Return** inq_grp_full_ncid_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_grp_full_ncid_Return* inq_grp_full_ncid_return_v;
    unsigned long pos;

    inq_grp_full_ncid_return_v = (Inq_grp_full_ncid_Return*)ast_alloc(rt,sizeof(Inq_grp_full_ncid_Return));
    if(inq_grp_full_ncid_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_grp_full_ncid_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_grp_full_ncid_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_grp_full_ncid_return_v->groupncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_grp_full_ncid_return_vp) *inq_grp_full_ncid_return_vp = inq_grp_full_ncid_return_v;
done:
    return ACATCH(status);
} /*Inq_grp_full_ncid_Return_read*/

ast_err
Inq_grp_full_ncid_Return_reclaim(ast_runtime* rt, Inq_grp_full_ncid_Return* inq_grp_full_ncid_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_grp_full_ncid_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_grp_full_ncid_Return_reclaim*/

size_t
Inq_grp_full_ncid_Return_get_size(ast_runtime* rt, Inq_grp_full_ncid_Return* inq_grp_full_ncid_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grp_full_ncid_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_grp_full_ncid_return_v->groupncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_grp_full_ncid_Return_get_size*/

ast_err
Inq_varids_write(ast_runtime* rt, Inq_varids* inq_varids_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_varids_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_varids_write*/

ast_err
Inq_varids_read(ast_runtime* rt, Inq_varids** inq_varids_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_varids* inq_varids_v;
    unsigned long pos;

    inq_varids_v = (Inq_varids*)ast_alloc(rt,sizeof(Inq_varids));
    if(inq_varids_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_varids|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_varids_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_varids_vp) *inq_varids_vp = inq_varids_v;
done:
    return ACATCH(status);
} /*Inq_varids_read*/

ast_err
Inq_varids_reclaim(ast_runtime* rt, Inq_varids* inq_varids_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_varids_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_varids_reclaim*/

size_t
Inq_varids_get_size(ast_runtime* rt, Inq_varids* inq_varids_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_varids_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_varids_get_size*/

ast_err
Inq_varids_Return_write(ast_runtime* rt, Inq_varids_Return* inq_varids_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_varids_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_varids_return_v->nvars);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_varids_return_v->varids.count;i++) {
            status = ast_write_primitive(rt,ast_int32,3,&inq_varids_return_v->varids.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Inq_varids_Return_write*/

ast_err
Inq_varids_Return_read(ast_runtime* rt, Inq_varids_Return** inq_varids_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_varids_Return* inq_varids_return_v;
    unsigned long pos;

    inq_varids_return_v = (Inq_varids_Return*)ast_alloc(rt,sizeof(Inq_varids_Return));
    if(inq_varids_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_varids_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_varids_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_varids_return_v->nvars);
            } break;
        case 3: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&inq_varids_return_v->varids,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_varids_return_vp) *inq_varids_return_vp = inq_varids_return_v;
done:
    return ACATCH(status);
} /*Inq_varids_Return_read*/

ast_err
Inq_varids_Return_reclaim(ast_runtime* rt, Inq_varids_Return* inq_varids_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_varids_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_varids_Return_reclaim*/

size_t
Inq_varids_Return_get_size(ast_runtime* rt, Inq_varids_Return* inq_varids_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_varids_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_varids_return_v->nvars);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_varids_return_v->varids.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_int32,&inq_varids_return_v->varids.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_varids_Return_get_size*/

ast_err
Inq_dimids_write(ast_runtime* rt, Inq_dimids* inq_dimids_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_dimids_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,2,&inq_dimids_v->includeparents);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_dimids_write*/

ast_err
Inq_dimids_read(ast_runtime* rt, Inq_dimids** inq_dimids_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_dimids* inq_dimids_v;
    unsigned long pos;

    inq_dimids_v = (Inq_dimids*)ast_alloc(rt,sizeof(Inq_dimids));
    if(inq_dimids_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_dimids|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_dimids_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_bool,2,&inq_dimids_v->includeparents);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_dimids_vp) *inq_dimids_vp = inq_dimids_v;
done:
    return ACATCH(status);
} /*Inq_dimids_read*/

ast_err
Inq_dimids_reclaim(ast_runtime* rt, Inq_dimids* inq_dimids_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_dimids_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_dimids_reclaim*/

size_t
Inq_dimids_get_size(ast_runtime* rt, Inq_dimids* inq_dimids_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dimids_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_bool,&inq_dimids_v->includeparents);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_dimids_get_size*/

ast_err
Inq_dimids_Return_write(ast_runtime* rt, Inq_dimids_Return* inq_dimids_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_dimids_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_dimids_return_v->ndims);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_dimids_return_v->dimids.count;i++) {
            status = ast_write_primitive(rt,ast_int32,3,&inq_dimids_return_v->dimids.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Inq_dimids_Return_write*/

ast_err
Inq_dimids_Return_read(ast_runtime* rt, Inq_dimids_Return** inq_dimids_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_dimids_Return* inq_dimids_return_v;
    unsigned long pos;

    inq_dimids_return_v = (Inq_dimids_Return*)ast_alloc(rt,sizeof(Inq_dimids_Return));
    if(inq_dimids_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_dimids_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_dimids_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_dimids_return_v->ndims);
            } break;
        case 3: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&inq_dimids_return_v->dimids,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_dimids_return_vp) *inq_dimids_return_vp = inq_dimids_return_v;
done:
    return ACATCH(status);
} /*Inq_dimids_Return_read*/

ast_err
Inq_dimids_Return_reclaim(ast_runtime* rt, Inq_dimids_Return* inq_dimids_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_dimids_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_dimids_Return_reclaim*/

size_t
Inq_dimids_Return_get_size(ast_runtime* rt, Inq_dimids_Return* inq_dimids_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dimids_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_dimids_return_v->ndims);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_dimids_return_v->dimids.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_int32,&inq_dimids_return_v->dimids.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_dimids_Return_get_size*/

ast_err
Inq_typeids_write(ast_runtime* rt, Inq_typeids* inq_typeids_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_typeids_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_typeids_write*/

ast_err
Inq_typeids_read(ast_runtime* rt, Inq_typeids** inq_typeids_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_typeids* inq_typeids_v;
    unsigned long pos;

    inq_typeids_v = (Inq_typeids*)ast_alloc(rt,sizeof(Inq_typeids));
    if(inq_typeids_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_typeids|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_typeids_v->ncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_typeids_vp) *inq_typeids_vp = inq_typeids_v;
done:
    return ACATCH(status);
} /*Inq_typeids_read*/

ast_err
Inq_typeids_reclaim(ast_runtime* rt, Inq_typeids* inq_typeids_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_typeids_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_typeids_reclaim*/

size_t
Inq_typeids_get_size(ast_runtime* rt, Inq_typeids* inq_typeids_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_typeids_v->ncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_typeids_get_size*/

ast_err
Inq_typeids_Return_write(ast_runtime* rt, Inq_typeids_Return* inq_typeids_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_typeids_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_typeids_return_v->ntypes);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_typeids_return_v->typeids.count;i++) {
            status = ast_write_primitive(rt,ast_int32,3,&inq_typeids_return_v->typeids.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Inq_typeids_Return_write*/

ast_err
Inq_typeids_Return_read(ast_runtime* rt, Inq_typeids_Return** inq_typeids_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_typeids_Return* inq_typeids_return_v;
    unsigned long pos;

    inq_typeids_return_v = (Inq_typeids_Return*)ast_alloc(rt,sizeof(Inq_typeids_Return));
    if(inq_typeids_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_typeids_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_typeids_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_typeids_return_v->ntypes);
            } break;
        case 3: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,3,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&inq_typeids_return_v->typeids,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_typeids_return_vp) *inq_typeids_return_vp = inq_typeids_return_v;
done:
    return ACATCH(status);
} /*Inq_typeids_Return_read*/

ast_err
Inq_typeids_Return_reclaim(ast_runtime* rt, Inq_typeids_Return* inq_typeids_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_typeids_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_typeids_Return_reclaim*/

size_t
Inq_typeids_Return_get_size(ast_runtime* rt, Inq_typeids_Return* inq_typeids_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_typeids_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_typeids_return_v->ntypes);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_typeids_return_v->typeids.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,3);
            fieldsize += ast_get_size(rt,ast_int32,&inq_typeids_return_v->typeids.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_typeids_Return_get_size*/

ast_err
Inq_type_equal_write(ast_runtime* rt, Inq_type_equal* inq_type_equal_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_type_equal_v->ncid1);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_type_equal_v->typeid1);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&inq_type_equal_v->ncid2);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,4,&inq_type_equal_v->typeid2);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_type_equal_write*/

ast_err
Inq_type_equal_read(ast_runtime* rt, Inq_type_equal** inq_type_equal_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_type_equal* inq_type_equal_v;
    unsigned long pos;

    inq_type_equal_v = (Inq_type_equal*)ast_alloc(rt,sizeof(Inq_type_equal));
    if(inq_type_equal_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_type_equal|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_type_equal_v->ncid1);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_type_equal_v->typeid1);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&inq_type_equal_v->ncid2);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_int32,4,&inq_type_equal_v->typeid2);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_type_equal_vp) *inq_type_equal_vp = inq_type_equal_v;
done:
    return ACATCH(status);
} /*Inq_type_equal_read*/

ast_err
Inq_type_equal_reclaim(ast_runtime* rt, Inq_type_equal* inq_type_equal_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_type_equal_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_type_equal_reclaim*/

size_t
Inq_type_equal_get_size(ast_runtime* rt, Inq_type_equal* inq_type_equal_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_type_equal_v->ncid1);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_type_equal_v->typeid1);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&inq_type_equal_v->ncid2);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_int32,&inq_type_equal_v->typeid2);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_type_equal_get_size*/

ast_err
Inq_type_equal_Return_write(ast_runtime* rt, Inq_type_equal_Return* inq_type_equal_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_type_equal_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,2,&inq_type_equal_return_v->equal);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_type_equal_Return_write*/

ast_err
Inq_type_equal_Return_read(ast_runtime* rt, Inq_type_equal_Return** inq_type_equal_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_type_equal_Return* inq_type_equal_return_v;
    unsigned long pos;

    inq_type_equal_return_v = (Inq_type_equal_Return*)ast_alloc(rt,sizeof(Inq_type_equal_Return));
    if(inq_type_equal_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_type_equal_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_type_equal_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_bool,2,&inq_type_equal_return_v->equal);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_type_equal_return_vp) *inq_type_equal_return_vp = inq_type_equal_return_v;
done:
    return ACATCH(status);
} /*Inq_type_equal_Return_read*/

ast_err
Inq_type_equal_Return_reclaim(ast_runtime* rt, Inq_type_equal_Return* inq_type_equal_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_type_equal_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_type_equal_Return_reclaim*/

size_t
Inq_type_equal_Return_get_size(ast_runtime* rt, Inq_type_equal_Return* inq_type_equal_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_type_equal_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_bool,&inq_type_equal_return_v->equal);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_type_equal_Return_get_size*/

ast_err
Def_grp_write(ast_runtime* rt, Def_grp* def_grp_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_grp_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&def_grp_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_grp_write*/

ast_err
Def_grp_read(ast_runtime* rt, Def_grp** def_grp_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_grp* def_grp_v;
    unsigned long pos;

    def_grp_v = (Def_grp*)ast_alloc(rt,sizeof(Def_grp));
    if(def_grp_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_grp|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_grp_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&def_grp_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_grp_vp) *def_grp_vp = def_grp_v;
done:
    return ACATCH(status);
} /*Def_grp_read*/

ast_err
Def_grp_reclaim(ast_runtime* rt, Def_grp* def_grp_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,def_grp_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)def_grp_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_grp_reclaim*/

size_t
Def_grp_get_size(ast_runtime* rt, Def_grp* def_grp_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_grp_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&def_grp_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_grp_get_size*/

ast_err
Def_grp_Return_write(ast_runtime* rt, Def_grp_Return* def_grp_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_grp_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_grp_return_v->grpncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_grp_Return_write*/

ast_err
Def_grp_Return_read(ast_runtime* rt, Def_grp_Return** def_grp_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_grp_Return* def_grp_return_v;
    unsigned long pos;

    def_grp_return_v = (Def_grp_Return*)ast_alloc(rt,sizeof(Def_grp_Return));
    if(def_grp_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_grp_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_grp_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_grp_return_v->grpncid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_grp_return_vp) *def_grp_return_vp = def_grp_return_v;
done:
    return ACATCH(status);
} /*Def_grp_Return_read*/

ast_err
Def_grp_Return_reclaim(ast_runtime* rt, Def_grp_Return* def_grp_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_grp_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_grp_Return_reclaim*/

size_t
Def_grp_Return_get_size(ast_runtime* rt, Def_grp_Return* def_grp_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_grp_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_grp_return_v->grpncid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_grp_Return_get_size*/

ast_err
Inq_user_type_write(ast_runtime* rt, Inq_user_type* inq_user_type_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_user_type_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_user_type_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_user_type_write*/

ast_err
Inq_user_type_read(ast_runtime* rt, Inq_user_type** inq_user_type_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_user_type* inq_user_type_v;
    unsigned long pos;

    inq_user_type_v = (Inq_user_type*)ast_alloc(rt,sizeof(Inq_user_type));
    if(inq_user_type_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_user_type|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_user_type_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_user_type_v->typeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_user_type_vp) *inq_user_type_vp = inq_user_type_v;
done:
    return ACATCH(status);
} /*Inq_user_type_read*/

ast_err
Inq_user_type_reclaim(ast_runtime* rt, Inq_user_type* inq_user_type_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_user_type_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_user_type_reclaim*/

size_t
Inq_user_type_get_size(ast_runtime* rt, Inq_user_type* inq_user_type_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_user_type_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_user_type_v->typeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_user_type_get_size*/

ast_err
Inq_user_type_Return_write(ast_runtime* rt, Inq_user_type_Return* inq_user_type_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_user_type_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_user_type_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&inq_user_type_return_v->size);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,4,&inq_user_type_return_v->basetype);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,5,&inq_user_type_return_v->nfields);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,6,&inq_user_type_return_v->typeclass);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_user_type_Return_write*/

ast_err
Inq_user_type_Return_read(ast_runtime* rt, Inq_user_type_Return** inq_user_type_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_user_type_Return* inq_user_type_return_v;
    unsigned long pos;

    inq_user_type_return_v = (Inq_user_type_Return*)ast_alloc(rt,sizeof(Inq_user_type_Return));
    if(inq_user_type_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_user_type_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_user_type_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_user_type_return_v->name);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&inq_user_type_return_v->size);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_int32,4,&inq_user_type_return_v->basetype);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_uint64,5,&inq_user_type_return_v->nfields);
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_int32,6,&inq_user_type_return_v->typeclass);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_user_type_return_vp) *inq_user_type_return_vp = inq_user_type_return_v;
done:
    return ACATCH(status);
} /*Inq_user_type_Return_read*/

ast_err
Inq_user_type_Return_reclaim(ast_runtime* rt, Inq_user_type_Return* inq_user_type_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_user_type_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_user_type_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_user_type_Return_reclaim*/

size_t
Inq_user_type_Return_get_size(ast_runtime* rt, Inq_user_type_Return* inq_user_type_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_user_type_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_user_type_return_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&inq_user_type_return_v->size);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_int32,&inq_user_type_return_v->basetype);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_uint64,&inq_user_type_return_v->nfields);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_int32,&inq_user_type_return_v->typeclass);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_user_type_Return_get_size*/

ast_err
Inq_typeid_write(ast_runtime* rt, Inq_typeid* inq_typeid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_typeid_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_typeid_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_typeid_write*/

ast_err
Inq_typeid_read(ast_runtime* rt, Inq_typeid** inq_typeid_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_typeid* inq_typeid_v;
    unsigned long pos;

    inq_typeid_v = (Inq_typeid*)ast_alloc(rt,sizeof(Inq_typeid));
    if(inq_typeid_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_typeid|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_typeid_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_typeid_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_typeid_vp) *inq_typeid_vp = inq_typeid_v;
done:
    return ACATCH(status);
} /*Inq_typeid_read*/

ast_err
Inq_typeid_reclaim(ast_runtime* rt, Inq_typeid* inq_typeid_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_typeid_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_typeid_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_typeid_reclaim*/

size_t
Inq_typeid_get_size(ast_runtime* rt, Inq_typeid* inq_typeid_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_typeid_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_typeid_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_typeid_get_size*/

ast_err
Inq_typeid_Return_write(ast_runtime* rt, Inq_typeid_Return* inq_typeid_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_typeid_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_typeid_return_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_typeid_Return_write*/

ast_err
Inq_typeid_Return_read(ast_runtime* rt, Inq_typeid_Return** inq_typeid_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_typeid_Return* inq_typeid_return_v;
    unsigned long pos;

    inq_typeid_return_v = (Inq_typeid_Return*)ast_alloc(rt,sizeof(Inq_typeid_Return));
    if(inq_typeid_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_typeid_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_typeid_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_typeid_return_v->typeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_typeid_return_vp) *inq_typeid_return_vp = inq_typeid_return_v;
done:
    return ACATCH(status);
} /*Inq_typeid_Return_read*/

ast_err
Inq_typeid_Return_reclaim(ast_runtime* rt, Inq_typeid_Return* inq_typeid_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_typeid_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_typeid_Return_reclaim*/

size_t
Inq_typeid_Return_get_size(ast_runtime* rt, Inq_typeid_Return* inq_typeid_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_typeid_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_typeid_return_v->typeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_typeid_Return_get_size*/

ast_err
Def_compound_write(ast_runtime* rt, Def_compound* def_compound_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_compound_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,2,&def_compound_v->size);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&def_compound_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_compound_write*/

ast_err
Def_compound_read(ast_runtime* rt, Def_compound** def_compound_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_compound* def_compound_v;
    unsigned long pos;

    def_compound_v = (Def_compound*)ast_alloc(rt,sizeof(Def_compound));
    if(def_compound_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_compound|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_compound_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_uint64,2,&def_compound_v->size);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&def_compound_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_compound_vp) *def_compound_vp = def_compound_v;
done:
    return ACATCH(status);
} /*Def_compound_read*/

ast_err
Def_compound_reclaim(ast_runtime* rt, Def_compound* def_compound_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,def_compound_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)def_compound_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_compound_reclaim*/

size_t
Def_compound_get_size(ast_runtime* rt, Def_compound* def_compound_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_compound_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_uint64,&def_compound_v->size);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&def_compound_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_compound_get_size*/

ast_err
Def_compound_Return_write(ast_runtime* rt, Def_compound_Return* def_compound_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_compound_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_compound_return_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_compound_Return_write*/

ast_err
Def_compound_Return_read(ast_runtime* rt, Def_compound_Return** def_compound_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_compound_Return* def_compound_return_v;
    unsigned long pos;

    def_compound_return_v = (Def_compound_Return*)ast_alloc(rt,sizeof(Def_compound_Return));
    if(def_compound_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_compound_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_compound_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_compound_return_v->typeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_compound_return_vp) *def_compound_return_vp = def_compound_return_v;
done:
    return ACATCH(status);
} /*Def_compound_Return_read*/

ast_err
Def_compound_Return_reclaim(ast_runtime* rt, Def_compound_Return* def_compound_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_compound_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_compound_Return_reclaim*/

size_t
Def_compound_Return_get_size(ast_runtime* rt, Def_compound_Return* def_compound_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_compound_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_compound_return_v->typeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_compound_Return_get_size*/

ast_err
Insert_compound_write(ast_runtime* rt, Insert_compound* insert_compound_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&insert_compound_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&insert_compound_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&insert_compound_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,4,&insert_compound_v->offset);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,5,&insert_compound_v->fieldtypeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Insert_compound_write*/

ast_err
Insert_compound_read(ast_runtime* rt, Insert_compound** insert_compound_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Insert_compound* insert_compound_v;
    unsigned long pos;

    insert_compound_v = (Insert_compound*)ast_alloc(rt,sizeof(Insert_compound));
    if(insert_compound_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Insert_compound|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&insert_compound_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&insert_compound_v->typeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&insert_compound_v->name);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_uint64,4,&insert_compound_v->offset);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_int32,5,&insert_compound_v->fieldtypeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(insert_compound_vp) *insert_compound_vp = insert_compound_v;
done:
    return ACATCH(status);
} /*Insert_compound_read*/

ast_err
Insert_compound_reclaim(ast_runtime* rt, Insert_compound* insert_compound_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,insert_compound_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)insert_compound_v);
    goto done;

done:
    return ACATCH(status);

} /*Insert_compound_reclaim*/

size_t
Insert_compound_get_size(ast_runtime* rt, Insert_compound* insert_compound_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&insert_compound_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&insert_compound_v->typeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&insert_compound_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_uint64,&insert_compound_v->offset);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_int32,&insert_compound_v->fieldtypeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Insert_compound_get_size*/

ast_err
Insert_compound_Return_write(ast_runtime* rt, Insert_compound_Return* insert_compound_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&insert_compound_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Insert_compound_Return_write*/

ast_err
Insert_compound_Return_read(ast_runtime* rt, Insert_compound_Return** insert_compound_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Insert_compound_Return* insert_compound_return_v;
    unsigned long pos;

    insert_compound_return_v = (Insert_compound_Return*)ast_alloc(rt,sizeof(Insert_compound_Return));
    if(insert_compound_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Insert_compound_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&insert_compound_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(insert_compound_return_vp) *insert_compound_return_vp = insert_compound_return_v;
done:
    return ACATCH(status);
} /*Insert_compound_Return_read*/

ast_err
Insert_compound_Return_reclaim(ast_runtime* rt, Insert_compound_Return* insert_compound_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)insert_compound_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Insert_compound_Return_reclaim*/

size_t
Insert_compound_Return_get_size(ast_runtime* rt, Insert_compound_Return* insert_compound_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&insert_compound_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Insert_compound_Return_get_size*/

ast_err
Insert_array_compound_write(ast_runtime* rt, Insert_array_compound* insert_array_compound_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&insert_array_compound_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&insert_array_compound_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&insert_array_compound_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,4,&insert_array_compound_v->offset);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,5,&insert_array_compound_v->fieldtypeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,6,&insert_array_compound_v->ndims);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<insert_array_compound_v->dimsizes.count;i++) {
            status = ast_write_primitive(rt,ast_int32,7,&insert_array_compound_v->dimsizes.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Insert_array_compound_write*/

ast_err
Insert_array_compound_read(ast_runtime* rt, Insert_array_compound** insert_array_compound_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Insert_array_compound* insert_array_compound_v;
    unsigned long pos;

    insert_array_compound_v = (Insert_array_compound*)ast_alloc(rt,sizeof(Insert_array_compound));
    if(insert_array_compound_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Insert_array_compound|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&insert_array_compound_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&insert_array_compound_v->typeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&insert_array_compound_v->name);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_uint64,4,&insert_array_compound_v->offset);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_int32,5,&insert_array_compound_v->fieldtypeid);
            } break;
        case 6: {
            status = ast_read_primitive(rt,ast_int32,6,&insert_array_compound_v->ndims);
            } break;
        case 7: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,7,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&insert_array_compound_v->dimsizes,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(insert_array_compound_vp) *insert_array_compound_vp = insert_array_compound_v;
done:
    return ACATCH(status);
} /*Insert_array_compound_read*/

ast_err
Insert_array_compound_reclaim(ast_runtime* rt, Insert_array_compound* insert_array_compound_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,insert_array_compound_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)insert_array_compound_v);
    goto done;

done:
    return ACATCH(status);

} /*Insert_array_compound_reclaim*/

size_t
Insert_array_compound_get_size(ast_runtime* rt, Insert_array_compound* insert_array_compound_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&insert_array_compound_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&insert_array_compound_v->typeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&insert_array_compound_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_uint64,&insert_array_compound_v->offset);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_int32,&insert_array_compound_v->fieldtypeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,6);
        fieldsize += ast_get_size(rt,ast_int32,&insert_array_compound_v->ndims);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<insert_array_compound_v->dimsizes.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,7);
            fieldsize += ast_get_size(rt,ast_int32,&insert_array_compound_v->dimsizes.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Insert_array_compound_get_size*/

ast_err
Insert_array_compound_Return_write(ast_runtime* rt, Insert_array_compound_Return* insert_array_compound_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&insert_array_compound_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Insert_array_compound_Return_write*/

ast_err
Insert_array_compound_Return_read(ast_runtime* rt, Insert_array_compound_Return** insert_array_compound_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Insert_array_compound_Return* insert_array_compound_return_v;
    unsigned long pos;

    insert_array_compound_return_v = (Insert_array_compound_Return*)ast_alloc(rt,sizeof(Insert_array_compound_Return));
    if(insert_array_compound_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Insert_array_compound_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&insert_array_compound_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(insert_array_compound_return_vp) *insert_array_compound_return_vp = insert_array_compound_return_v;
done:
    return ACATCH(status);
} /*Insert_array_compound_Return_read*/

ast_err
Insert_array_compound_Return_reclaim(ast_runtime* rt, Insert_array_compound_Return* insert_array_compound_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)insert_array_compound_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Insert_array_compound_Return_reclaim*/

size_t
Insert_array_compound_Return_get_size(ast_runtime* rt, Insert_array_compound_Return* insert_array_compound_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&insert_array_compound_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Insert_array_compound_Return_get_size*/

ast_err
Inq_compound_field_write(ast_runtime* rt, Inq_compound_field* inq_compound_field_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_compound_field_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_compound_field_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&inq_compound_field_v->fieldid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_compound_field_write*/

ast_err
Inq_compound_field_read(ast_runtime* rt, Inq_compound_field** inq_compound_field_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_compound_field* inq_compound_field_v;
    unsigned long pos;

    inq_compound_field_v = (Inq_compound_field*)ast_alloc(rt,sizeof(Inq_compound_field));
    if(inq_compound_field_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_compound_field|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_compound_field_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_compound_field_v->typeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&inq_compound_field_v->fieldid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_compound_field_vp) *inq_compound_field_vp = inq_compound_field_v;
done:
    return ACATCH(status);
} /*Inq_compound_field_read*/

ast_err
Inq_compound_field_reclaim(ast_runtime* rt, Inq_compound_field* inq_compound_field_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_compound_field_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_compound_field_reclaim*/

size_t
Inq_compound_field_get_size(ast_runtime* rt, Inq_compound_field* inq_compound_field_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_field_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_field_v->typeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_field_v->fieldid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_compound_field_get_size*/

ast_err
Inq_compound_field_Return_write(ast_runtime* rt, Inq_compound_field_Return* inq_compound_field_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_compound_field_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_compound_field_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&inq_compound_field_return_v->offset);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,4,&inq_compound_field_return_v->fieldtypeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,5,&inq_compound_field_return_v->ndims);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<inq_compound_field_return_v->dimsizes.count;i++) {
            status = ast_write_primitive(rt,ast_int32,6,&inq_compound_field_return_v->dimsizes.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Inq_compound_field_Return_write*/

ast_err
Inq_compound_field_Return_read(ast_runtime* rt, Inq_compound_field_Return** inq_compound_field_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_compound_field_Return* inq_compound_field_return_v;
    unsigned long pos;

    inq_compound_field_return_v = (Inq_compound_field_Return*)ast_alloc(rt,sizeof(Inq_compound_field_Return));
    if(inq_compound_field_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_compound_field_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_compound_field_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_compound_field_return_v->name);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&inq_compound_field_return_v->offset);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_int32,4,&inq_compound_field_return_v->fieldtypeid);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_int32,5,&inq_compound_field_return_v->ndims);
            } break;
        case 6: {
            int32_t tmp;
            status = ast_read_primitive(rt,ast_int32,6,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_int32,&inq_compound_field_return_v->dimsizes,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_compound_field_return_vp) *inq_compound_field_return_vp = inq_compound_field_return_v;
done:
    return ACATCH(status);
} /*Inq_compound_field_Return_read*/

ast_err
Inq_compound_field_Return_reclaim(ast_runtime* rt, Inq_compound_field_Return* inq_compound_field_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_compound_field_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_compound_field_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_compound_field_Return_reclaim*/

size_t
Inq_compound_field_Return_get_size(ast_runtime* rt, Inq_compound_field_Return* inq_compound_field_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_field_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_compound_field_return_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&inq_compound_field_return_v->offset);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_field_return_v->fieldtypeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_field_return_v->ndims);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<inq_compound_field_return_v->dimsizes.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,6);
            fieldsize += ast_get_size(rt,ast_int32,&inq_compound_field_return_v->dimsizes.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_compound_field_Return_get_size*/

ast_err
Inq_compound_fieldindex_write(ast_runtime* rt, Inq_compound_fieldindex* inq_compound_fieldindex_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_compound_fieldindex_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_compound_fieldindex_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&inq_compound_fieldindex_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_compound_fieldindex_write*/

ast_err
Inq_compound_fieldindex_read(ast_runtime* rt, Inq_compound_fieldindex** inq_compound_fieldindex_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_compound_fieldindex* inq_compound_fieldindex_v;
    unsigned long pos;

    inq_compound_fieldindex_v = (Inq_compound_fieldindex*)ast_alloc(rt,sizeof(Inq_compound_fieldindex));
    if(inq_compound_fieldindex_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_compound_fieldindex|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_compound_fieldindex_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_compound_fieldindex_v->typeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&inq_compound_fieldindex_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_compound_fieldindex_vp) *inq_compound_fieldindex_vp = inq_compound_fieldindex_v;
done:
    return ACATCH(status);
} /*Inq_compound_fieldindex_read*/

ast_err
Inq_compound_fieldindex_reclaim(ast_runtime* rt, Inq_compound_fieldindex* inq_compound_fieldindex_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_compound_fieldindex_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_compound_fieldindex_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_compound_fieldindex_reclaim*/

size_t
Inq_compound_fieldindex_get_size(ast_runtime* rt, Inq_compound_fieldindex* inq_compound_fieldindex_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_fieldindex_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_fieldindex_v->typeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&inq_compound_fieldindex_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_compound_fieldindex_get_size*/

ast_err
Inq_compound_fieldindex_Return_write(ast_runtime* rt, Inq_compound_fieldindex_Return* inq_compound_fieldindex_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_compound_fieldindex_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_compound_fieldindex_return_v->fieldid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_compound_fieldindex_Return_write*/

ast_err
Inq_compound_fieldindex_Return_read(ast_runtime* rt, Inq_compound_fieldindex_Return** inq_compound_fieldindex_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_compound_fieldindex_Return* inq_compound_fieldindex_return_v;
    unsigned long pos;

    inq_compound_fieldindex_return_v = (Inq_compound_fieldindex_Return*)ast_alloc(rt,sizeof(Inq_compound_fieldindex_Return));
    if(inq_compound_fieldindex_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_compound_fieldindex_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_compound_fieldindex_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_compound_fieldindex_return_v->fieldid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_compound_fieldindex_return_vp) *inq_compound_fieldindex_return_vp = inq_compound_fieldindex_return_v;
done:
    return ACATCH(status);
} /*Inq_compound_fieldindex_Return_read*/

ast_err
Inq_compound_fieldindex_Return_reclaim(ast_runtime* rt, Inq_compound_fieldindex_Return* inq_compound_fieldindex_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_compound_fieldindex_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_compound_fieldindex_Return_reclaim*/

size_t
Inq_compound_fieldindex_Return_get_size(ast_runtime* rt, Inq_compound_fieldindex_Return* inq_compound_fieldindex_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_fieldindex_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_compound_fieldindex_return_v->fieldid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_compound_fieldindex_Return_get_size*/

ast_err
Def_vlen_write(ast_runtime* rt, Def_vlen* def_vlen_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_vlen_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&def_vlen_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&def_vlen_v->base_typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_vlen_write*/

ast_err
Def_vlen_read(ast_runtime* rt, Def_vlen** def_vlen_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_vlen* def_vlen_v;
    unsigned long pos;

    def_vlen_v = (Def_vlen*)ast_alloc(rt,sizeof(Def_vlen));
    if(def_vlen_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_vlen|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_vlen_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&def_vlen_v->name);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&def_vlen_v->base_typeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_vlen_vp) *def_vlen_vp = def_vlen_v;
done:
    return ACATCH(status);
} /*Def_vlen_read*/

ast_err
Def_vlen_reclaim(ast_runtime* rt, Def_vlen* def_vlen_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,def_vlen_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)def_vlen_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_vlen_reclaim*/

size_t
Def_vlen_get_size(ast_runtime* rt, Def_vlen* def_vlen_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_vlen_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&def_vlen_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&def_vlen_v->base_typeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_vlen_get_size*/

ast_err
Def_vlen_Return_write(ast_runtime* rt, Def_vlen_Return* def_vlen_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_vlen_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_vlen_return_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_vlen_Return_write*/

ast_err
Def_vlen_Return_read(ast_runtime* rt, Def_vlen_Return** def_vlen_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_vlen_Return* def_vlen_return_v;
    unsigned long pos;

    def_vlen_return_v = (Def_vlen_Return*)ast_alloc(rt,sizeof(Def_vlen_Return));
    if(def_vlen_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_vlen_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_vlen_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_vlen_return_v->typeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_vlen_return_vp) *def_vlen_return_vp = def_vlen_return_v;
done:
    return ACATCH(status);
} /*Def_vlen_Return_read*/

ast_err
Def_vlen_Return_reclaim(ast_runtime* rt, Def_vlen_Return* def_vlen_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_vlen_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_vlen_Return_reclaim*/

size_t
Def_vlen_Return_get_size(ast_runtime* rt, Def_vlen_Return* def_vlen_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_vlen_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_vlen_return_v->typeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_vlen_Return_get_size*/

ast_err
Put_vlen_element_write(ast_runtime* rt, Put_vlen_element* put_vlen_element_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_vlen_element_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&put_vlen_element_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,3,&put_vlen_element_v->element);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,4,&put_vlen_element_v->len);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,5,&put_vlen_element_v->data);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_vlen_element_write*/

ast_err
Put_vlen_element_read(ast_runtime* rt, Put_vlen_element** put_vlen_element_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_vlen_element* put_vlen_element_v;
    unsigned long pos;

    put_vlen_element_v = (Put_vlen_element*)ast_alloc(rt,sizeof(Put_vlen_element));
    if(put_vlen_element_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_vlen_element|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_vlen_element_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&put_vlen_element_v->typeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_bytes,3,&put_vlen_element_v->element);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_uint64,4,&put_vlen_element_v->len);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_bytes,5,&put_vlen_element_v->data);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_vlen_element_vp) *put_vlen_element_vp = put_vlen_element_v;
done:
    return ACATCH(status);
} /*Put_vlen_element_read*/

ast_err
Put_vlen_element_reclaim(ast_runtime* rt, Put_vlen_element* put_vlen_element_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&put_vlen_element_v->element);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_reclaim_bytes(rt,&put_vlen_element_v->data);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)put_vlen_element_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_vlen_element_reclaim*/

size_t
Put_vlen_element_get_size(ast_runtime* rt, Put_vlen_element* put_vlen_element_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_vlen_element_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&put_vlen_element_v->typeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_bytes,&put_vlen_element_v->element);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_uint64,&put_vlen_element_v->len);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_bytes,&put_vlen_element_v->data);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_vlen_element_get_size*/

ast_err
Put_vlen_element_Return_write(ast_runtime* rt, Put_vlen_element_Return* put_vlen_element_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&put_vlen_element_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Put_vlen_element_Return_write*/

ast_err
Put_vlen_element_Return_read(ast_runtime* rt, Put_vlen_element_Return** put_vlen_element_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Put_vlen_element_Return* put_vlen_element_return_v;
    unsigned long pos;

    put_vlen_element_return_v = (Put_vlen_element_Return*)ast_alloc(rt,sizeof(Put_vlen_element_Return));
    if(put_vlen_element_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Put_vlen_element_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&put_vlen_element_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(put_vlen_element_return_vp) *put_vlen_element_return_vp = put_vlen_element_return_v;
done:
    return ACATCH(status);
} /*Put_vlen_element_Return_read*/

ast_err
Put_vlen_element_Return_reclaim(ast_runtime* rt, Put_vlen_element_Return* put_vlen_element_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)put_vlen_element_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Put_vlen_element_Return_reclaim*/

size_t
Put_vlen_element_Return_get_size(ast_runtime* rt, Put_vlen_element_Return* put_vlen_element_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&put_vlen_element_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Put_vlen_element_Return_get_size*/

ast_err
Get_vlen_element_write(ast_runtime* rt, Get_vlen_element* get_vlen_element_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_vlen_element_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&get_vlen_element_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_vlen_element_write*/

ast_err
Get_vlen_element_read(ast_runtime* rt, Get_vlen_element** get_vlen_element_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_vlen_element* get_vlen_element_v;
    unsigned long pos;

    get_vlen_element_v = (Get_vlen_element*)ast_alloc(rt,sizeof(Get_vlen_element));
    if(get_vlen_element_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_vlen_element|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_vlen_element_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&get_vlen_element_v->typeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_vlen_element_vp) *get_vlen_element_vp = get_vlen_element_v;
done:
    return ACATCH(status);
} /*Get_vlen_element_read*/

ast_err
Get_vlen_element_reclaim(ast_runtime* rt, Get_vlen_element* get_vlen_element_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)get_vlen_element_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_vlen_element_reclaim*/

size_t
Get_vlen_element_get_size(ast_runtime* rt, Get_vlen_element* get_vlen_element_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_vlen_element_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&get_vlen_element_v->typeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_vlen_element_get_size*/

ast_err
Get_vlen_element_Return_write(ast_runtime* rt, Get_vlen_element_Return* get_vlen_element_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_vlen_element_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,2,&get_vlen_element_return_v->element);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&get_vlen_element_return_v->len);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,4,&get_vlen_element_return_v->data);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_vlen_element_Return_write*/

ast_err
Get_vlen_element_Return_read(ast_runtime* rt, Get_vlen_element_Return** get_vlen_element_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_vlen_element_Return* get_vlen_element_return_v;
    unsigned long pos;

    get_vlen_element_return_v = (Get_vlen_element_Return*)ast_alloc(rt,sizeof(Get_vlen_element_Return));
    if(get_vlen_element_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_vlen_element_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_vlen_element_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_bytes,2,&get_vlen_element_return_v->element);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&get_vlen_element_return_v->len);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_bytes,4,&get_vlen_element_return_v->data);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_vlen_element_return_vp) *get_vlen_element_return_vp = get_vlen_element_return_v;
done:
    return ACATCH(status);
} /*Get_vlen_element_Return_read*/

ast_err
Get_vlen_element_Return_reclaim(ast_runtime* rt, Get_vlen_element_Return* get_vlen_element_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&get_vlen_element_return_v->element);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_reclaim_bytes(rt,&get_vlen_element_return_v->data);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)get_vlen_element_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_vlen_element_Return_reclaim*/

size_t
Get_vlen_element_Return_get_size(ast_runtime* rt, Get_vlen_element_Return* get_vlen_element_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_vlen_element_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_bytes,&get_vlen_element_return_v->element);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&get_vlen_element_return_v->len);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_bytes,&get_vlen_element_return_v->data);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_vlen_element_Return_get_size*/

ast_err
Def_enum_write(ast_runtime* rt, Def_enum* def_enum_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_enum_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_enum_v->basetypeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&def_enum_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_enum_write*/

ast_err
Def_enum_read(ast_runtime* rt, Def_enum** def_enum_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_enum* def_enum_v;
    unsigned long pos;

    def_enum_v = (Def_enum*)ast_alloc(rt,sizeof(Def_enum));
    if(def_enum_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_enum|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_enum_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_enum_v->basetypeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&def_enum_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_enum_vp) *def_enum_vp = def_enum_v;
done:
    return ACATCH(status);
} /*Def_enum_read*/

ast_err
Def_enum_reclaim(ast_runtime* rt, Def_enum* def_enum_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,def_enum_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)def_enum_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_enum_reclaim*/

size_t
Def_enum_get_size(ast_runtime* rt, Def_enum* def_enum_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_enum_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_enum_v->basetypeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&def_enum_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_enum_get_size*/

ast_err
Def_enum_Return_write(ast_runtime* rt, Def_enum_Return* def_enum_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_enum_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_enum_return_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_enum_Return_write*/

ast_err
Def_enum_Return_read(ast_runtime* rt, Def_enum_Return** def_enum_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_enum_Return* def_enum_return_v;
    unsigned long pos;

    def_enum_return_v = (Def_enum_Return*)ast_alloc(rt,sizeof(Def_enum_Return));
    if(def_enum_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_enum_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_enum_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_enum_return_v->typeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_enum_return_vp) *def_enum_return_vp = def_enum_return_v;
done:
    return ACATCH(status);
} /*Def_enum_Return_read*/

ast_err
Def_enum_Return_reclaim(ast_runtime* rt, Def_enum_Return* def_enum_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_enum_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_enum_Return_reclaim*/

size_t
Def_enum_Return_get_size(ast_runtime* rt, Def_enum_Return* def_enum_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_enum_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_enum_return_v->typeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_enum_Return_get_size*/

ast_err
Insert_enum_write(ast_runtime* rt, Insert_enum* insert_enum_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&insert_enum_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&insert_enum_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&insert_enum_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,4,&insert_enum_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Insert_enum_write*/

ast_err
Insert_enum_read(ast_runtime* rt, Insert_enum** insert_enum_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Insert_enum* insert_enum_v;
    unsigned long pos;

    insert_enum_v = (Insert_enum*)ast_alloc(rt,sizeof(Insert_enum));
    if(insert_enum_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Insert_enum|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&insert_enum_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&insert_enum_v->typeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&insert_enum_v->name);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_bytes,4,&insert_enum_v->value);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(insert_enum_vp) *insert_enum_vp = insert_enum_v;
done:
    return ACATCH(status);
} /*Insert_enum_read*/

ast_err
Insert_enum_reclaim(ast_runtime* rt, Insert_enum* insert_enum_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,insert_enum_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_reclaim_bytes(rt,&insert_enum_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)insert_enum_v);
    goto done;

done:
    return ACATCH(status);

} /*Insert_enum_reclaim*/

size_t
Insert_enum_get_size(ast_runtime* rt, Insert_enum* insert_enum_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&insert_enum_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&insert_enum_v->typeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&insert_enum_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_bytes,&insert_enum_v->value);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Insert_enum_get_size*/

ast_err
Insert_enum_Return_write(ast_runtime* rt, Insert_enum_Return* insert_enum_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&insert_enum_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Insert_enum_Return_write*/

ast_err
Insert_enum_Return_read(ast_runtime* rt, Insert_enum_Return** insert_enum_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Insert_enum_Return* insert_enum_return_v;
    unsigned long pos;

    insert_enum_return_v = (Insert_enum_Return*)ast_alloc(rt,sizeof(Insert_enum_Return));
    if(insert_enum_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Insert_enum_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&insert_enum_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(insert_enum_return_vp) *insert_enum_return_vp = insert_enum_return_v;
done:
    return ACATCH(status);
} /*Insert_enum_Return_read*/

ast_err
Insert_enum_Return_reclaim(ast_runtime* rt, Insert_enum_Return* insert_enum_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)insert_enum_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Insert_enum_Return_reclaim*/

size_t
Insert_enum_Return_get_size(ast_runtime* rt, Insert_enum_Return* insert_enum_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&insert_enum_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Insert_enum_Return_get_size*/

ast_err
Inq_enum_member_write(ast_runtime* rt, Inq_enum_member* inq_enum_member_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_enum_member_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_enum_member_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,3,&inq_enum_member_v->index);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_enum_member_write*/

ast_err
Inq_enum_member_read(ast_runtime* rt, Inq_enum_member** inq_enum_member_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_enum_member* inq_enum_member_v;
    unsigned long pos;

    inq_enum_member_v = (Inq_enum_member*)ast_alloc(rt,sizeof(Inq_enum_member));
    if(inq_enum_member_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_enum_member|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_enum_member_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_enum_member_v->typeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_int32,3,&inq_enum_member_v->index);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_enum_member_vp) *inq_enum_member_vp = inq_enum_member_v;
done:
    return ACATCH(status);
} /*Inq_enum_member_read*/

ast_err
Inq_enum_member_reclaim(ast_runtime* rt, Inq_enum_member* inq_enum_member_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_enum_member_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_enum_member_reclaim*/

size_t
Inq_enum_member_get_size(ast_runtime* rt, Inq_enum_member* inq_enum_member_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_enum_member_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_enum_member_v->typeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_int32,&inq_enum_member_v->index);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_enum_member_get_size*/

ast_err
Inq_enum_member_Return_write(ast_runtime* rt, Inq_enum_member_Return* inq_enum_member_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_enum_member_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_enum_member_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,3,&inq_enum_member_return_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_enum_member_Return_write*/

ast_err
Inq_enum_member_Return_read(ast_runtime* rt, Inq_enum_member_Return** inq_enum_member_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_enum_member_Return* inq_enum_member_return_v;
    unsigned long pos;

    inq_enum_member_return_v = (Inq_enum_member_Return*)ast_alloc(rt,sizeof(Inq_enum_member_Return));
    if(inq_enum_member_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_enum_member_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_enum_member_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_enum_member_return_v->name);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_bytes,3,&inq_enum_member_return_v->value);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_enum_member_return_vp) *inq_enum_member_return_vp = inq_enum_member_return_v;
done:
    return ACATCH(status);
} /*Inq_enum_member_Return_read*/

ast_err
Inq_enum_member_Return_reclaim(ast_runtime* rt, Inq_enum_member_Return* inq_enum_member_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_enum_member_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_reclaim_bytes(rt,&inq_enum_member_return_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_enum_member_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_enum_member_Return_reclaim*/

size_t
Inq_enum_member_Return_get_size(ast_runtime* rt, Inq_enum_member_Return* inq_enum_member_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_enum_member_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_enum_member_return_v->name);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_bytes,&inq_enum_member_return_v->value);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_enum_member_Return_get_size*/

ast_err
Inq_enum_ident_write(ast_runtime* rt, Inq_enum_ident* inq_enum_ident_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_enum_ident_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&inq_enum_ident_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&inq_enum_ident_v->value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_enum_ident_write*/

ast_err
Inq_enum_ident_read(ast_runtime* rt, Inq_enum_ident** inq_enum_ident_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_enum_ident* inq_enum_ident_v;
    unsigned long pos;

    inq_enum_ident_v = (Inq_enum_ident*)ast_alloc(rt,sizeof(Inq_enum_ident));
    if(inq_enum_ident_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_enum_ident|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_enum_ident_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&inq_enum_ident_v->typeid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&inq_enum_ident_v->value);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_enum_ident_vp) *inq_enum_ident_vp = inq_enum_ident_v;
done:
    return ACATCH(status);
} /*Inq_enum_ident_read*/

ast_err
Inq_enum_ident_reclaim(ast_runtime* rt, Inq_enum_ident* inq_enum_ident_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)inq_enum_ident_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_enum_ident_reclaim*/

size_t
Inq_enum_ident_get_size(ast_runtime* rt, Inq_enum_ident* inq_enum_ident_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_enum_ident_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&inq_enum_ident_v->typeid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&inq_enum_ident_v->value);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_enum_ident_get_size*/

ast_err
Inq_enum_ident_Return_write(ast_runtime* rt, Inq_enum_ident_Return* inq_enum_ident_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&inq_enum_ident_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,2,&inq_enum_ident_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Inq_enum_ident_Return_write*/

ast_err
Inq_enum_ident_Return_read(ast_runtime* rt, Inq_enum_ident_Return** inq_enum_ident_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Inq_enum_ident_Return* inq_enum_ident_return_v;
    unsigned long pos;

    inq_enum_ident_return_v = (Inq_enum_ident_Return*)ast_alloc(rt,sizeof(Inq_enum_ident_Return));
    if(inq_enum_ident_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Inq_enum_ident_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&inq_enum_ident_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_string,2,&inq_enum_ident_return_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(inq_enum_ident_return_vp) *inq_enum_ident_return_vp = inq_enum_ident_return_v;
done:
    return ACATCH(status);
} /*Inq_enum_ident_Return_read*/

ast_err
Inq_enum_ident_Return_reclaim(ast_runtime* rt, Inq_enum_ident_Return* inq_enum_ident_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,inq_enum_ident_return_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)inq_enum_ident_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Inq_enum_ident_Return_reclaim*/

size_t
Inq_enum_ident_Return_get_size(ast_runtime* rt, Inq_enum_ident_Return* inq_enum_ident_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&inq_enum_ident_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_string,&inq_enum_ident_return_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Inq_enum_ident_Return_get_size*/

ast_err
Def_opaque_write(ast_runtime* rt, Def_opaque* def_opaque_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_opaque_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,2,&def_opaque_v->size);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_string,3,&def_opaque_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_opaque_write*/

ast_err
Def_opaque_read(ast_runtime* rt, Def_opaque** def_opaque_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_opaque* def_opaque_v;
    unsigned long pos;

    def_opaque_v = (Def_opaque*)ast_alloc(rt,sizeof(Def_opaque));
    if(def_opaque_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_opaque|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_opaque_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_uint64,2,&def_opaque_v->size);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_string,3,&def_opaque_v->name);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_opaque_vp) *def_opaque_vp = def_opaque_v;
done:
    return ACATCH(status);
} /*Def_opaque_read*/

ast_err
Def_opaque_reclaim(ast_runtime* rt, Def_opaque* def_opaque_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,def_opaque_v->name);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)def_opaque_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_opaque_reclaim*/

size_t
Def_opaque_get_size(ast_runtime* rt, Def_opaque* def_opaque_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_opaque_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_uint64,&def_opaque_v->size);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_string,&def_opaque_v->name);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_opaque_get_size*/

ast_err
Def_opaque_Return_write(ast_runtime* rt, Def_opaque_Return* def_opaque_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_opaque_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_opaque_return_v->typeid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_opaque_Return_write*/

ast_err
Def_opaque_Return_read(ast_runtime* rt, Def_opaque_Return** def_opaque_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_opaque_Return* def_opaque_return_v;
    unsigned long pos;

    def_opaque_return_v = (Def_opaque_Return*)ast_alloc(rt,sizeof(Def_opaque_Return));
    if(def_opaque_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_opaque_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_opaque_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_opaque_return_v->typeid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_opaque_return_vp) *def_opaque_return_vp = def_opaque_return_v;
done:
    return ACATCH(status);
} /*Def_opaque_Return_read*/

ast_err
Def_opaque_Return_reclaim(ast_runtime* rt, Def_opaque_Return* def_opaque_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_opaque_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_opaque_Return_reclaim*/

size_t
Def_opaque_Return_get_size(ast_runtime* rt, Def_opaque_Return* def_opaque_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_opaque_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_opaque_return_v->typeid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_opaque_Return_get_size*/

ast_err
Def_var_deflate_write(ast_runtime* rt, Def_var_deflate* def_var_deflate_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_deflate_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_var_deflate_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,3,&def_var_deflate_v->shuffle);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,4,&def_var_deflate_v->deflate);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,5,&def_var_deflate_v->deflatelevel);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_deflate_write*/

ast_err
Def_var_deflate_read(ast_runtime* rt, Def_var_deflate** def_var_deflate_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_deflate* def_var_deflate_v;
    unsigned long pos;

    def_var_deflate_v = (Def_var_deflate*)ast_alloc(rt,sizeof(Def_var_deflate));
    if(def_var_deflate_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_deflate|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_deflate_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_var_deflate_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_bool,3,&def_var_deflate_v->shuffle);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_bool,4,&def_var_deflate_v->deflate);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_int32,5,&def_var_deflate_v->deflatelevel);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_deflate_vp) *def_var_deflate_vp = def_var_deflate_v;
done:
    return ACATCH(status);
} /*Def_var_deflate_read*/

ast_err
Def_var_deflate_reclaim(ast_runtime* rt, Def_var_deflate* def_var_deflate_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_deflate_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_deflate_reclaim*/

size_t
Def_var_deflate_get_size(ast_runtime* rt, Def_var_deflate* def_var_deflate_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_deflate_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_deflate_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_bool,&def_var_deflate_v->shuffle);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_bool,&def_var_deflate_v->deflate);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_deflate_v->deflatelevel);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_deflate_get_size*/

ast_err
Def_var_deflate_Return_write(ast_runtime* rt, Def_var_deflate_Return* def_var_deflate_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_deflate_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_deflate_Return_write*/

ast_err
Def_var_deflate_Return_read(ast_runtime* rt, Def_var_deflate_Return** def_var_deflate_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_deflate_Return* def_var_deflate_return_v;
    unsigned long pos;

    def_var_deflate_return_v = (Def_var_deflate_Return*)ast_alloc(rt,sizeof(Def_var_deflate_Return));
    if(def_var_deflate_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_deflate_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_deflate_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_deflate_return_vp) *def_var_deflate_return_vp = def_var_deflate_return_v;
done:
    return ACATCH(status);
} /*Def_var_deflate_Return_read*/

ast_err
Def_var_deflate_Return_reclaim(ast_runtime* rt, Def_var_deflate_Return* def_var_deflate_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_deflate_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_deflate_Return_reclaim*/

size_t
Def_var_deflate_Return_get_size(ast_runtime* rt, Def_var_deflate_Return* def_var_deflate_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_deflate_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_deflate_Return_get_size*/

ast_err
Def_var_fletcher32_write(ast_runtime* rt, Def_var_fletcher32* def_var_fletcher32_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_fletcher32_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_var_fletcher32_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,3,&def_var_fletcher32_v->fletcher32);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_fletcher32_write*/

ast_err
Def_var_fletcher32_read(ast_runtime* rt, Def_var_fletcher32** def_var_fletcher32_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_fletcher32* def_var_fletcher32_v;
    unsigned long pos;

    def_var_fletcher32_v = (Def_var_fletcher32*)ast_alloc(rt,sizeof(Def_var_fletcher32));
    if(def_var_fletcher32_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_fletcher32|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_fletcher32_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_var_fletcher32_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_bool,3,&def_var_fletcher32_v->fletcher32);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_fletcher32_vp) *def_var_fletcher32_vp = def_var_fletcher32_v;
done:
    return ACATCH(status);
} /*Def_var_fletcher32_read*/

ast_err
Def_var_fletcher32_reclaim(ast_runtime* rt, Def_var_fletcher32* def_var_fletcher32_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_fletcher32_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_fletcher32_reclaim*/

size_t
Def_var_fletcher32_get_size(ast_runtime* rt, Def_var_fletcher32* def_var_fletcher32_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_fletcher32_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_fletcher32_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_bool,&def_var_fletcher32_v->fletcher32);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_fletcher32_get_size*/

ast_err
Def_var_fletcher32_Return_write(ast_runtime* rt, Def_var_fletcher32_Return* def_var_fletcher32_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_fletcher32_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_fletcher32_Return_write*/

ast_err
Def_var_fletcher32_Return_read(ast_runtime* rt, Def_var_fletcher32_Return** def_var_fletcher32_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_fletcher32_Return* def_var_fletcher32_return_v;
    unsigned long pos;

    def_var_fletcher32_return_v = (Def_var_fletcher32_Return*)ast_alloc(rt,sizeof(Def_var_fletcher32_Return));
    if(def_var_fletcher32_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_fletcher32_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_fletcher32_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_fletcher32_return_vp) *def_var_fletcher32_return_vp = def_var_fletcher32_return_v;
done:
    return ACATCH(status);
} /*Def_var_fletcher32_Return_read*/

ast_err
Def_var_fletcher32_Return_reclaim(ast_runtime* rt, Def_var_fletcher32_Return* def_var_fletcher32_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_fletcher32_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_fletcher32_Return_reclaim*/

size_t
Def_var_fletcher32_Return_get_size(ast_runtime* rt, Def_var_fletcher32_Return* def_var_fletcher32_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_fletcher32_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_fletcher32_Return_get_size*/

ast_err
Def_var_chunking_write(ast_runtime* rt, Def_var_chunking* def_var_chunking_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_chunking_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_var_chunking_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,3,&def_var_chunking_v->contiguous);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        int i = 0;
        for(i=0;i<def_var_chunking_v->chunksizes.count;i++) {
            status = ast_write_primitive(rt,ast_uint64,4,&def_var_chunking_v->chunksizes.values[i]);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }
    }

done:
    return ACATCH(status);

} /*Def_var_chunking_write*/

ast_err
Def_var_chunking_read(ast_runtime* rt, Def_var_chunking** def_var_chunking_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_chunking* def_var_chunking_v;
    unsigned long pos;

    def_var_chunking_v = (Def_var_chunking*)ast_alloc(rt,sizeof(Def_var_chunking));
    if(def_var_chunking_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_chunking|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_chunking_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_var_chunking_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_bool,3,&def_var_chunking_v->contiguous);
            } break;
        case 4: {
            uint64_t tmp;
            status = ast_read_primitive(rt,ast_uint64,4,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            status = ast_repeat_append(rt,ast_uint64,&def_var_chunking_v->chunksizes,&tmp);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_chunking_vp) *def_var_chunking_vp = def_var_chunking_v;
done:
    return ACATCH(status);
} /*Def_var_chunking_read*/

ast_err
Def_var_chunking_reclaim(ast_runtime* rt, Def_var_chunking* def_var_chunking_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_chunking_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_chunking_reclaim*/

size_t
Def_var_chunking_get_size(ast_runtime* rt, Def_var_chunking* def_var_chunking_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_chunking_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_chunking_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_bool,&def_var_chunking_v->contiguous);
        totalsize += fieldsize;
    }
    {
        int i;
        for(i=0;i<def_var_chunking_v->chunksizes.count;i++) {
            fieldsize += ast_get_tagsize(rt,ast_counted,4);
            fieldsize += ast_get_size(rt,ast_uint64,&def_var_chunking_v->chunksizes.values[i]);
        }
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_chunking_get_size*/

ast_err
Def_var_chunking_Return_write(ast_runtime* rt, Def_var_chunking_Return* def_var_chunking_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_chunking_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_chunking_Return_write*/

ast_err
Def_var_chunking_Return_read(ast_runtime* rt, Def_var_chunking_Return** def_var_chunking_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_chunking_Return* def_var_chunking_return_v;
    unsigned long pos;

    def_var_chunking_return_v = (Def_var_chunking_Return*)ast_alloc(rt,sizeof(Def_var_chunking_Return));
    if(def_var_chunking_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_chunking_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_chunking_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_chunking_return_vp) *def_var_chunking_return_vp = def_var_chunking_return_v;
done:
    return ACATCH(status);
} /*Def_var_chunking_Return_read*/

ast_err
Def_var_chunking_Return_reclaim(ast_runtime* rt, Def_var_chunking_Return* def_var_chunking_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_chunking_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_chunking_Return_reclaim*/

size_t
Def_var_chunking_Return_get_size(ast_runtime* rt, Def_var_chunking_Return* def_var_chunking_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_chunking_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_chunking_Return_get_size*/

ast_err
Def_var_fill_write(ast_runtime* rt, Def_var_fill* def_var_fill_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_fill_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_var_fill_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,3,&def_var_fill_v->nofill);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bytes,4,&def_var_fill_v->fill_value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_fill_write*/

ast_err
Def_var_fill_read(ast_runtime* rt, Def_var_fill** def_var_fill_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_fill* def_var_fill_v;
    unsigned long pos;

    def_var_fill_v = (Def_var_fill*)ast_alloc(rt,sizeof(Def_var_fill));
    if(def_var_fill_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_fill|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_fill_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_var_fill_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_bool,3,&def_var_fill_v->nofill);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_bytes,4,&def_var_fill_v->fill_value);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_fill_vp) *def_var_fill_vp = def_var_fill_v;
done:
    return ACATCH(status);
} /*Def_var_fill_read*/

ast_err
Def_var_fill_reclaim(ast_runtime* rt, Def_var_fill* def_var_fill_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_bytes(rt,&def_var_fill_v->fill_value);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)def_var_fill_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_fill_reclaim*/

size_t
Def_var_fill_get_size(ast_runtime* rt, Def_var_fill* def_var_fill_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_fill_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_fill_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_bool,&def_var_fill_v->nofill);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_bytes,&def_var_fill_v->fill_value);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_fill_get_size*/

ast_err
Def_var_fill_Return_write(ast_runtime* rt, Def_var_fill_Return* def_var_fill_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_fill_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_fill_Return_write*/

ast_err
Def_var_fill_Return_read(ast_runtime* rt, Def_var_fill_Return** def_var_fill_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_fill_Return* def_var_fill_return_v;
    unsigned long pos;

    def_var_fill_return_v = (Def_var_fill_Return*)ast_alloc(rt,sizeof(Def_var_fill_Return));
    if(def_var_fill_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_fill_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_fill_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_fill_return_vp) *def_var_fill_return_vp = def_var_fill_return_v;
done:
    return ACATCH(status);
} /*Def_var_fill_Return_read*/

ast_err
Def_var_fill_Return_reclaim(ast_runtime* rt, Def_var_fill_Return* def_var_fill_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_fill_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_fill_Return_reclaim*/

size_t
Def_var_fill_Return_get_size(ast_runtime* rt, Def_var_fill_Return* def_var_fill_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_fill_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_fill_Return_get_size*/

ast_err
Def_var_endian_write(ast_runtime* rt, Def_var_endian* def_var_endian_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_endian_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&def_var_endian_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_bool,3,&def_var_endian_v->bigendian);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_endian_write*/

ast_err
Def_var_endian_read(ast_runtime* rt, Def_var_endian** def_var_endian_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_endian* def_var_endian_v;
    unsigned long pos;

    def_var_endian_v = (Def_var_endian*)ast_alloc(rt,sizeof(Def_var_endian));
    if(def_var_endian_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_endian|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_endian_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&def_var_endian_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_bool,3,&def_var_endian_v->bigendian);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_endian_vp) *def_var_endian_vp = def_var_endian_v;
done:
    return ACATCH(status);
} /*Def_var_endian_read*/

ast_err
Def_var_endian_reclaim(ast_runtime* rt, Def_var_endian* def_var_endian_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_endian_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_endian_reclaim*/

size_t
Def_var_endian_get_size(ast_runtime* rt, Def_var_endian* def_var_endian_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_endian_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_endian_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_bool,&def_var_endian_v->bigendian);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_endian_get_size*/

ast_err
Def_var_endian_Return_write(ast_runtime* rt, Def_var_endian_Return* def_var_endian_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&def_var_endian_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Def_var_endian_Return_write*/

ast_err
Def_var_endian_Return_read(ast_runtime* rt, Def_var_endian_Return** def_var_endian_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Def_var_endian_Return* def_var_endian_return_v;
    unsigned long pos;

    def_var_endian_return_v = (Def_var_endian_Return*)ast_alloc(rt,sizeof(Def_var_endian_Return));
    if(def_var_endian_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Def_var_endian_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&def_var_endian_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(def_var_endian_return_vp) *def_var_endian_return_vp = def_var_endian_return_v;
done:
    return ACATCH(status);
} /*Def_var_endian_Return_read*/

ast_err
Def_var_endian_Return_reclaim(ast_runtime* rt, Def_var_endian_Return* def_var_endian_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)def_var_endian_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Def_var_endian_Return_reclaim*/

size_t
Def_var_endian_Return_get_size(ast_runtime* rt, Def_var_endian_Return* def_var_endian_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&def_var_endian_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Def_var_endian_Return_get_size*/

ast_err
Set_var_chunk_cache_write(ast_runtime* rt, Set_var_chunk_cache* set_var_chunk_cache_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&set_var_chunk_cache_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&set_var_chunk_cache_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&set_var_chunk_cache_v->size);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,4,&set_var_chunk_cache_v->nelems);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_float,5,&set_var_chunk_cache_v->preemption);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Set_var_chunk_cache_write*/

ast_err
Set_var_chunk_cache_read(ast_runtime* rt, Set_var_chunk_cache** set_var_chunk_cache_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Set_var_chunk_cache* set_var_chunk_cache_v;
    unsigned long pos;

    set_var_chunk_cache_v = (Set_var_chunk_cache*)ast_alloc(rt,sizeof(Set_var_chunk_cache));
    if(set_var_chunk_cache_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Set_var_chunk_cache|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&set_var_chunk_cache_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&set_var_chunk_cache_v->varid);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&set_var_chunk_cache_v->size);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_uint64,4,&set_var_chunk_cache_v->nelems);
            } break;
        case 5: {
            status = ast_read_primitive(rt,ast_float,5,&set_var_chunk_cache_v->preemption);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(set_var_chunk_cache_vp) *set_var_chunk_cache_vp = set_var_chunk_cache_v;
done:
    return ACATCH(status);
} /*Set_var_chunk_cache_read*/

ast_err
Set_var_chunk_cache_reclaim(ast_runtime* rt, Set_var_chunk_cache* set_var_chunk_cache_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)set_var_chunk_cache_v);
    goto done;

done:
    return ACATCH(status);

} /*Set_var_chunk_cache_reclaim*/

size_t
Set_var_chunk_cache_get_size(ast_runtime* rt, Set_var_chunk_cache* set_var_chunk_cache_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&set_var_chunk_cache_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&set_var_chunk_cache_v->varid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&set_var_chunk_cache_v->size);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_uint64,&set_var_chunk_cache_v->nelems);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,5);
        fieldsize += ast_get_size(rt,ast_float,&set_var_chunk_cache_v->preemption);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Set_var_chunk_cache_get_size*/

ast_err
Set_var_chunk_cache_Return_write(ast_runtime* rt, Set_var_chunk_cache_Return* set_var_chunk_cache_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&set_var_chunk_cache_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Set_var_chunk_cache_Return_write*/

ast_err
Set_var_chunk_cache_Return_read(ast_runtime* rt, Set_var_chunk_cache_Return** set_var_chunk_cache_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Set_var_chunk_cache_Return* set_var_chunk_cache_return_v;
    unsigned long pos;

    set_var_chunk_cache_return_v = (Set_var_chunk_cache_Return*)ast_alloc(rt,sizeof(Set_var_chunk_cache_Return));
    if(set_var_chunk_cache_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Set_var_chunk_cache_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&set_var_chunk_cache_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(set_var_chunk_cache_return_vp) *set_var_chunk_cache_return_vp = set_var_chunk_cache_return_v;
done:
    return ACATCH(status);
} /*Set_var_chunk_cache_Return_read*/

ast_err
Set_var_chunk_cache_Return_reclaim(ast_runtime* rt, Set_var_chunk_cache_Return* set_var_chunk_cache_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)set_var_chunk_cache_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Set_var_chunk_cache_Return_reclaim*/

size_t
Set_var_chunk_cache_Return_get_size(ast_runtime* rt, Set_var_chunk_cache_Return* set_var_chunk_cache_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&set_var_chunk_cache_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Set_var_chunk_cache_Return_get_size*/

ast_err
Get_var_chunk_cache_write(ast_runtime* rt, Get_var_chunk_cache* get_var_chunk_cache_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_var_chunk_cache_v->ncid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&get_var_chunk_cache_v->varid);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_var_chunk_cache_write*/

ast_err
Get_var_chunk_cache_read(ast_runtime* rt, Get_var_chunk_cache** get_var_chunk_cache_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_var_chunk_cache* get_var_chunk_cache_v;
    unsigned long pos;

    get_var_chunk_cache_v = (Get_var_chunk_cache*)ast_alloc(rt,sizeof(Get_var_chunk_cache));
    if(get_var_chunk_cache_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_var_chunk_cache|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_var_chunk_cache_v->ncid);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&get_var_chunk_cache_v->varid);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_var_chunk_cache_vp) *get_var_chunk_cache_vp = get_var_chunk_cache_v;
done:
    return ACATCH(status);
} /*Get_var_chunk_cache_read*/

ast_err
Get_var_chunk_cache_reclaim(ast_runtime* rt, Get_var_chunk_cache* get_var_chunk_cache_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)get_var_chunk_cache_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_var_chunk_cache_reclaim*/

size_t
Get_var_chunk_cache_get_size(ast_runtime* rt, Get_var_chunk_cache* get_var_chunk_cache_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_var_chunk_cache_v->ncid);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&get_var_chunk_cache_v->varid);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_var_chunk_cache_get_size*/

ast_err
Get_var_chunk_cache_Return_write(ast_runtime* rt, Get_var_chunk_cache_Return* get_var_chunk_cache_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&get_var_chunk_cache_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,2,&get_var_chunk_cache_return_v->size);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_uint64,3,&get_var_chunk_cache_return_v->nelems);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_float,4,&get_var_chunk_cache_return_v->preemption);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*Get_var_chunk_cache_Return_write*/

ast_err
Get_var_chunk_cache_Return_read(ast_runtime* rt, Get_var_chunk_cache_Return** get_var_chunk_cache_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    Get_var_chunk_cache_Return* get_var_chunk_cache_return_v;
    unsigned long pos;

    get_var_chunk_cache_return_v = (Get_var_chunk_cache_Return*)ast_alloc(rt,sizeof(Get_var_chunk_cache_Return));
    if(get_var_chunk_cache_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|Get_var_chunk_cache_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&get_var_chunk_cache_return_v->ncstatus);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_uint64,2,&get_var_chunk_cache_return_v->size);
            } break;
        case 3: {
            status = ast_read_primitive(rt,ast_uint64,3,&get_var_chunk_cache_return_v->nelems);
            } break;
        case 4: {
            status = ast_read_primitive(rt,ast_float,4,&get_var_chunk_cache_return_v->preemption);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(get_var_chunk_cache_return_vp) *get_var_chunk_cache_return_vp = get_var_chunk_cache_return_v;
done:
    return ACATCH(status);
} /*Get_var_chunk_cache_Return_read*/

ast_err
Get_var_chunk_cache_Return_reclaim(ast_runtime* rt, Get_var_chunk_cache_Return* get_var_chunk_cache_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)get_var_chunk_cache_return_v);
    goto done;

done:
    return ACATCH(status);

} /*Get_var_chunk_cache_Return_reclaim*/

size_t
Get_var_chunk_cache_Return_get_size(ast_runtime* rt, Get_var_chunk_cache_Return* get_var_chunk_cache_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&get_var_chunk_cache_return_v->ncstatus);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_uint64,&get_var_chunk_cache_return_v->size);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,3);
        fieldsize += ast_get_size(rt,ast_uint64,&get_var_chunk_cache_return_v->nelems);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,4);
        fieldsize += ast_get_size(rt,ast_float,&get_var_chunk_cache_return_v->preemption);
        totalsize += fieldsize;
    }
    return totalsize;

} /*Get_var_chunk_cache_Return_get_size*/

ast_err
NC_set_log_level_write(ast_runtime* rt, NC_set_log_level* nc_set_log_level_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&nc_set_log_level_v->newlevel);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*NC_set_log_level_write*/

ast_err
NC_set_log_level_read(ast_runtime* rt, NC_set_log_level** nc_set_log_level_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    NC_set_log_level* nc_set_log_level_v;
    unsigned long pos;

    nc_set_log_level_v = (NC_set_log_level*)ast_alloc(rt,sizeof(NC_set_log_level));
    if(nc_set_log_level_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|NC_set_log_level|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&nc_set_log_level_v->newlevel);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(nc_set_log_level_vp) *nc_set_log_level_vp = nc_set_log_level_v;
done:
    return ACATCH(status);
} /*NC_set_log_level_read*/

ast_err
NC_set_log_level_reclaim(ast_runtime* rt, NC_set_log_level* nc_set_log_level_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)nc_set_log_level_v);
    goto done;

done:
    return ACATCH(status);

} /*NC_set_log_level_reclaim*/

size_t
NC_set_log_level_get_size(ast_runtime* rt, NC_set_log_level* nc_set_log_level_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&nc_set_log_level_v->newlevel);
        totalsize += fieldsize;
    }
    return totalsize;

} /*NC_set_log_level_get_size*/

ast_err
NC_set_log_level_Return_write(ast_runtime* rt, NC_set_log_level_Return* nc_set_log_level_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&nc_set_log_level_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*NC_set_log_level_Return_write*/

ast_err
NC_set_log_level_Return_read(ast_runtime* rt, NC_set_log_level_Return** nc_set_log_level_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    NC_set_log_level_Return* nc_set_log_level_return_v;
    unsigned long pos;

    nc_set_log_level_return_v = (NC_set_log_level_Return*)ast_alloc(rt,sizeof(NC_set_log_level_Return));
    if(nc_set_log_level_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|NC_set_log_level_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&nc_set_log_level_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(nc_set_log_level_return_vp) *nc_set_log_level_return_vp = nc_set_log_level_return_v;
done:
    return ACATCH(status);
} /*NC_set_log_level_Return_read*/

ast_err
NC_set_log_level_Return_reclaim(ast_runtime* rt, NC_set_log_level_Return* nc_set_log_level_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)nc_set_log_level_return_v);
    goto done;

done:
    return ACATCH(status);

} /*NC_set_log_level_Return_reclaim*/

size_t
NC_set_log_level_Return_get_size(ast_runtime* rt, NC_set_log_level_Return* nc_set_log_level_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&nc_set_log_level_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*NC_set_log_level_Return_get_size*/

ast_err
NC_inq_libvers_write(ast_runtime* rt, NC_inq_libvers* nc_inq_libvers_v)
{
    ast_err status = AST_NOERR;


    return ACATCH(status);

} /*NC_inq_libvers_write*/

ast_err
NC_inq_libvers_read(ast_runtime* rt, NC_inq_libvers** nc_inq_libvers_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    NC_inq_libvers* nc_inq_libvers_v;
    unsigned long pos;

    nc_inq_libvers_v = (NC_inq_libvers*)ast_alloc(rt,sizeof(NC_inq_libvers));
    if(nc_inq_libvers_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|NC_inq_libvers|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(nc_inq_libvers_vp) *nc_inq_libvers_vp = nc_inq_libvers_v;
done:
    return ACATCH(status);
} /*NC_inq_libvers_read*/

ast_err
NC_inq_libvers_reclaim(ast_runtime* rt, NC_inq_libvers* nc_inq_libvers_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)nc_inq_libvers_v);
    goto done;

done:
    return ACATCH(status);

} /*NC_inq_libvers_reclaim*/

size_t
NC_inq_libvers_get_size(ast_runtime* rt, NC_inq_libvers* nc_inq_libvers_v)
{
    size_t totalsize = 0;

    return totalsize;

} /*NC_inq_libvers_get_size*/

ast_err
NC_inq_libvers_Return_write(ast_runtime* rt, NC_inq_libvers_Return* nc_inq_libvers_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_string,1,&nc_inq_libvers_return_v->version);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*NC_inq_libvers_Return_write*/

ast_err
NC_inq_libvers_Return_read(ast_runtime* rt, NC_inq_libvers_Return** nc_inq_libvers_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    NC_inq_libvers_Return* nc_inq_libvers_return_v;
    unsigned long pos;

    nc_inq_libvers_return_v = (NC_inq_libvers_Return*)ast_alloc(rt,sizeof(NC_inq_libvers_Return));
    if(nc_inq_libvers_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|NC_inq_libvers_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_string,1,&nc_inq_libvers_return_v->version);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(nc_inq_libvers_return_vp) *nc_inq_libvers_return_vp = nc_inq_libvers_return_v;
done:
    return ACATCH(status);
} /*NC_inq_libvers_Return_read*/

ast_err
NC_inq_libvers_Return_reclaim(ast_runtime* rt, NC_inq_libvers_Return* nc_inq_libvers_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,nc_inq_libvers_return_v->version);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)nc_inq_libvers_return_v);
    goto done;

done:
    return ACATCH(status);

} /*NC_inq_libvers_Return_reclaim*/

size_t
NC_inq_libvers_Return_get_size(ast_runtime* rt, NC_inq_libvers_Return* nc_inq_libvers_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_string,&nc_inq_libvers_return_v->version);
        totalsize += fieldsize;
    }
    return totalsize;

} /*NC_inq_libvers_Return_get_size*/

ast_err
NC_delete_mp_write(ast_runtime* rt, NC_delete_mp* nc_delete_mp_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_string,1,&nc_delete_mp_v->path);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    {
        status = ast_write_primitive(rt,ast_int32,2,&nc_delete_mp_v->basepe);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*NC_delete_mp_write*/

ast_err
NC_delete_mp_read(ast_runtime* rt, NC_delete_mp** nc_delete_mp_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    NC_delete_mp* nc_delete_mp_v;
    unsigned long pos;

    nc_delete_mp_v = (NC_delete_mp*)ast_alloc(rt,sizeof(NC_delete_mp));
    if(nc_delete_mp_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|NC_delete_mp|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_string,1,&nc_delete_mp_v->path);
            } break;
        case 2: {
            status = ast_read_primitive(rt,ast_int32,2,&nc_delete_mp_v->basepe);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(nc_delete_mp_vp) *nc_delete_mp_vp = nc_delete_mp_v;
done:
    return ACATCH(status);
} /*NC_delete_mp_read*/

ast_err
NC_delete_mp_reclaim(ast_runtime* rt, NC_delete_mp* nc_delete_mp_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_reclaim_string(rt,nc_delete_mp_v->path);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }
    ast_free(rt,(void*)nc_delete_mp_v);
    goto done;

done:
    return ACATCH(status);

} /*NC_delete_mp_reclaim*/

size_t
NC_delete_mp_get_size(ast_runtime* rt, NC_delete_mp* nc_delete_mp_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_string,&nc_delete_mp_v->path);
        totalsize += fieldsize;
    }
    {
        fieldsize += ast_get_tagsize(rt,ast_counted,2);
        fieldsize += ast_get_size(rt,ast_int32,&nc_delete_mp_v->basepe);
        totalsize += fieldsize;
    }
    return totalsize;

} /*NC_delete_mp_get_size*/

ast_err
NC_delete_mp_Return_write(ast_runtime* rt, NC_delete_mp_Return* nc_delete_mp_return_v)
{
    ast_err status = AST_NOERR;

    {
        status = ast_write_primitive(rt,ast_int32,1,&nc_delete_mp_return_v->ncstatus);
        if(status != AST_NOERR) {ACATCH(status); goto done;}
    }

done:
    return ACATCH(status);

} /*NC_delete_mp_Return_write*/

ast_err
NC_delete_mp_Return_read(ast_runtime* rt, NC_delete_mp_Return** nc_delete_mp_return_vp)
{
    ast_err status = AST_NOERR;
    uint32_t wiretype, fieldno;
    NC_delete_mp_Return* nc_delete_mp_return_v;
    unsigned long pos;

    nc_delete_mp_return_v = (NC_delete_mp_Return*)ast_alloc(rt,sizeof(NC_delete_mp_Return));
    if(nc_delete_mp_return_v == NULL) return AST_ENOMEM;

    while(status == AST_NOERR) {
        pos = (unsigned long)xpos(rt);
        status = ast_read_tag(rt,&wiretype,&fieldno);
        if(status == AST_EOF) {status = AST_NOERR; break;}
        if(status != AST_NOERR) break;
        {
        fprintf(stderr,"|NC_delete_mp_Return|: before=%lu fieldno=%lu wiretype=%lu after=%lu\n",pos,(unsigned long)fieldno,(unsigned long)wiretype,(unsigned long)xpos(rt));
        }
        switch (fieldno) {
        case 1: {
            status = ast_read_primitive(rt,ast_int32,1,&nc_delete_mp_return_v->ncstatus);
            } break;
        default:
            status = ast_skip_field(rt,wiretype,fieldno);
            if(status != AST_NOERR) {ACATCH(status); goto done;}
        }; /*switch*/
    };/*while*/
    if(status != AST_NOERR) {ACATCH(status); goto done;}
    if(nc_delete_mp_return_vp) *nc_delete_mp_return_vp = nc_delete_mp_return_v;
done:
    return ACATCH(status);
} /*NC_delete_mp_Return_read*/

ast_err
NC_delete_mp_Return_reclaim(ast_runtime* rt, NC_delete_mp_Return* nc_delete_mp_return_v)
{
    ast_err status = AST_NOERR;

    ast_free(rt,(void*)nc_delete_mp_return_v);
    goto done;

done:
    return ACATCH(status);

} /*NC_delete_mp_Return_reclaim*/

size_t
NC_delete_mp_Return_get_size(ast_runtime* rt, NC_delete_mp_Return* nc_delete_mp_return_v)
{
    size_t totalsize = 0;
    size_t fieldsize = 0;

    {
        fieldsize += ast_get_tagsize(rt,ast_counted,1);
        fieldsize += ast_get_size(rt,ast_int32,&nc_delete_mp_return_v->ncstatus);
        totalsize += fieldsize;
    }
    return totalsize;

} /*NC_delete_mp_Return_get_size*/


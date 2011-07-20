#ifndef PROTORPC_H
#define PROTORPC_H


/* Forward definitions */
typedef struct Create Create;
typedef struct Create_Return Create_Return;
typedef struct Open Open;
typedef struct Open_Return Open_Return;
typedef struct Redef Redef;
typedef struct Redef_Return Redef_Return;
typedef struct _Enddef _Enddef;
typedef struct _Enddef_Return _Enddef_Return;
typedef struct Sync Sync;
typedef struct Sync_Return Sync_Return;
typedef struct Abort Abort;
typedef struct Abort_Return Abort_Return;
typedef struct Close Close;
typedef struct Close_Return Close_Return;
typedef struct Set_fill Set_fill;
typedef struct Set_fill_Return Set_fill_Return;
typedef struct Inq_base_pe Inq_base_pe;
typedef struct Inq_base_pe_Return Inq_base_pe_Return;
typedef struct Set_base_pe Set_base_pe;
typedef struct Set_base_pe_Return Set_base_pe_Return;
typedef struct Inq_format Inq_format;
typedef struct Inq_format_Return Inq_format_Return;
typedef struct Inq Inq;
typedef struct Inq_Return Inq_Return;
typedef struct Inq_type Inq_type;
typedef struct Inq_type_Return Inq_type_Return;
typedef struct Def_dim Def_dim;
typedef struct Def_dim_Return Def_dim_Return;
typedef struct Inq_dimid Inq_dimid;
typedef struct Inq_dimid_Return Inq_dimid_Return;
typedef struct Inq_dim Inq_dim;
typedef struct Inq_dim_Return Inq_dim_Return;
typedef struct Inq_unlimdim Inq_unlimdim;
typedef struct Inq_unlimdim_Return Inq_unlimdim_Return;
typedef struct Rename_dim Rename_dim;
typedef struct Rename_dim_Return Rename_dim_Return;
typedef struct Inq_att Inq_att;
typedef struct Inq_att_Return Inq_att_Return;
typedef struct Inq_attid Inq_attid;
typedef struct Inq_attid_Return Inq_attid_Return;
typedef struct Inq_attname Inq_attname;
typedef struct Inq_attname_Return Inq_attname_Return;
typedef struct Rename_att Rename_att;
typedef struct Rename_att_Return Rename_att_Return;
typedef struct Del_att Del_att;
typedef struct Del_att_Return Del_att_Return;
typedef struct Get_att Get_att;
typedef struct Get_att_Return Get_att_Return;
typedef struct Put_att Put_att;
typedef struct Put_att_Return Put_att_Return;
typedef struct Def_var Def_var;
typedef struct Def_var_Return Def_var_Return;
typedef struct Inq_varid Inq_varid;
typedef struct Inq_varid_Return Inq_varid_Return;
typedef struct Rename_var Rename_var;
typedef struct Rename_var_Return Rename_var_Return;
typedef struct Get_vara Get_vara;
typedef struct Get_vara_Return Get_vara_Return;
typedef struct Put_vara Put_vara;
typedef struct Put_vara_Return Put_vara_Return;
typedef struct Get_vars Get_vars;
typedef struct Get_vars_Return Get_vars_Return;
typedef struct Put_vars Put_vars;
typedef struct Put_vars_Return Put_vars_Return;
typedef struct Get_varm Get_varm;
typedef struct Get_varm_Return Get_varm_Return;
typedef struct Put_varm Put_varm;
typedef struct Put_varm_Return Put_varm_Return;
typedef struct Inq_var_all Inq_var_all;
typedef struct Inq_var_all_Return Inq_var_all_Return;
typedef struct Show_metadata Show_metadata;
typedef struct Show_metadata_Return Show_metadata_Return;
typedef struct Inq_unlimdims Inq_unlimdims;
typedef struct Inq_unlimdims_Return Inq_unlimdims_Return;
typedef struct Var_par_access Var_par_access;
typedef struct Var_par_access_Return Var_par_access_Return;
typedef struct Inq_ncid Inq_ncid;
typedef struct Inq_ncid_Return Inq_ncid_Return;
typedef struct Inq_grps Inq_grps;
typedef struct Inq_grps_Return Inq_grps_Return;
typedef struct Inq_grpname Inq_grpname;
typedef struct Inq_grpname_Return Inq_grpname_Return;
typedef struct Inq_grpname_full Inq_grpname_full;
typedef struct Inq_grpname_full_Return Inq_grpname_full_Return;
typedef struct Inq_grp_parent Inq_grp_parent;
typedef struct Inq_grp_parent_Return Inq_grp_parent_Return;
typedef struct Inq_grp_full_ncid Inq_grp_full_ncid;
typedef struct Inq_grp_full_ncid_Return Inq_grp_full_ncid_Return;
typedef struct Inq_varids Inq_varids;
typedef struct Inq_varids_Return Inq_varids_Return;
typedef struct Inq_dimids Inq_dimids;
typedef struct Inq_dimids_Return Inq_dimids_Return;
typedef struct Inq_typeids Inq_typeids;
typedef struct Inq_typeids_Return Inq_typeids_Return;
typedef struct Inq_type_equal Inq_type_equal;
typedef struct Inq_type_equal_Return Inq_type_equal_Return;
typedef struct Def_grp Def_grp;
typedef struct Def_grp_Return Def_grp_Return;
typedef struct Inq_user_type Inq_user_type;
typedef struct Inq_user_type_Return Inq_user_type_Return;
typedef struct Inq_typeid Inq_typeid;
typedef struct Inq_typeid_Return Inq_typeid_Return;
typedef struct Def_compound Def_compound;
typedef struct Def_compound_Return Def_compound_Return;
typedef struct Insert_compound Insert_compound;
typedef struct Insert_compound_Return Insert_compound_Return;
typedef struct Insert_array_compound Insert_array_compound;
typedef struct Insert_array_compound_Return Insert_array_compound_Return;
typedef struct Inq_compound_field Inq_compound_field;
typedef struct Inq_compound_field_Return Inq_compound_field_Return;
typedef struct Inq_compound_fieldindex Inq_compound_fieldindex;
typedef struct Inq_compound_fieldindex_Return Inq_compound_fieldindex_Return;
typedef struct Def_vlen Def_vlen;
typedef struct Def_vlen_Return Def_vlen_Return;
typedef struct Put_vlen_element Put_vlen_element;
typedef struct Put_vlen_element_Return Put_vlen_element_Return;
typedef struct Get_vlen_element Get_vlen_element;
typedef struct Get_vlen_element_Return Get_vlen_element_Return;
typedef struct Def_enum Def_enum;
typedef struct Def_enum_Return Def_enum_Return;
typedef struct Insert_enum Insert_enum;
typedef struct Insert_enum_Return Insert_enum_Return;
typedef struct Inq_enum_member Inq_enum_member;
typedef struct Inq_enum_member_Return Inq_enum_member_Return;
typedef struct Inq_enum_ident Inq_enum_ident;
typedef struct Inq_enum_ident_Return Inq_enum_ident_Return;
typedef struct Def_opaque Def_opaque;
typedef struct Def_opaque_Return Def_opaque_Return;
typedef struct Def_var_deflate Def_var_deflate;
typedef struct Def_var_deflate_Return Def_var_deflate_Return;
typedef struct Def_var_fletcher32 Def_var_fletcher32;
typedef struct Def_var_fletcher32_Return Def_var_fletcher32_Return;
typedef struct Def_var_chunking Def_var_chunking;
typedef struct Def_var_chunking_Return Def_var_chunking_Return;
typedef struct Def_var_fill Def_var_fill;
typedef struct Def_var_fill_Return Def_var_fill_Return;
typedef struct Def_var_endian Def_var_endian;
typedef struct Def_var_endian_Return Def_var_endian_Return;
typedef struct Set_var_chunk_cache Set_var_chunk_cache;
typedef struct Set_var_chunk_cache_Return Set_var_chunk_cache_Return;
typedef struct Get_var_chunk_cache Get_var_chunk_cache;
typedef struct Get_var_chunk_cache_Return Get_var_chunk_cache_Return;
typedef struct NC_set_log_level NC_set_log_level;
typedef struct NC_set_log_level_Return NC_set_log_level_Return;
typedef struct NC_inq_libvers NC_inq_libvers;
typedef struct NC_inq_libvers_Return NC_inq_libvers_Return;
typedef struct NC_delete_mp NC_delete_mp;
typedef struct NC_delete_mp_Return NC_delete_mp_Return;

struct Create {
    char* path;
    int32_t cmode;
    uint64_t initialsz;
    int32_t basepe;
    struct {size_t count; int64_t* values;} chunksizehint;
    int32_t use_parallel;
    bytes_t parameters;
};


extern ast_err Create_write(ast_runtime*,Create*);
extern ast_err Create_read(ast_runtime*,Create**);
extern ast_err Create_reclaim(ast_runtime*,Create*);
extern size_t Create_get_size(ast_runtime*,Create*);

struct Create_Return {
    int32_t ncid;
};


extern ast_err Create_Return_write(ast_runtime*,Create_Return*);
extern ast_err Create_Return_read(ast_runtime*,Create_Return**);
extern ast_err Create_Return_reclaim(ast_runtime*,Create_Return*);
extern size_t Create_Return_get_size(ast_runtime*,Create_Return*);

struct Open {
    char* path;
    int32_t mode;
    int32_t basepe;
    struct {size_t count; uint64_t* values;} chunksizehint;
    int32_t use_parallel;
    bytes_t parameters;
};


extern ast_err Open_write(ast_runtime*,Open*);
extern ast_err Open_read(ast_runtime*,Open**);
extern ast_err Open_reclaim(ast_runtime*,Open*);
extern size_t Open_get_size(ast_runtime*,Open*);

struct Open_Return {
    int32_t ncstatus;
    int32_t ncid;
};


extern ast_err Open_Return_write(ast_runtime*,Open_Return*);
extern ast_err Open_Return_read(ast_runtime*,Open_Return**);
extern ast_err Open_Return_reclaim(ast_runtime*,Open_Return*);
extern size_t Open_Return_get_size(ast_runtime*,Open_Return*);

struct Redef {
    int32_t ncid;
};


extern ast_err Redef_write(ast_runtime*,Redef*);
extern ast_err Redef_read(ast_runtime*,Redef**);
extern ast_err Redef_reclaim(ast_runtime*,Redef*);
extern size_t Redef_get_size(ast_runtime*,Redef*);

struct Redef_Return {
    int32_t ncstatus;
};


extern ast_err Redef_Return_write(ast_runtime*,Redef_Return*);
extern ast_err Redef_Return_read(ast_runtime*,Redef_Return**);
extern ast_err Redef_Return_reclaim(ast_runtime*,Redef_Return*);
extern size_t Redef_Return_get_size(ast_runtime*,Redef_Return*);

struct _Enddef {
    int32_t ncid;
    uint64_t minfree;
    uint64_t v_align;
    uint64_t v_minfree;
    uint64_t r_align;
};


extern ast_err _Enddef_write(ast_runtime*,_Enddef*);
extern ast_err _Enddef_read(ast_runtime*,_Enddef**);
extern ast_err _Enddef_reclaim(ast_runtime*,_Enddef*);
extern size_t _Enddef_get_size(ast_runtime*,_Enddef*);

struct _Enddef_Return {
    int32_t ncstatus;
};


extern ast_err _Enddef_Return_write(ast_runtime*,_Enddef_Return*);
extern ast_err _Enddef_Return_read(ast_runtime*,_Enddef_Return**);
extern ast_err _Enddef_Return_reclaim(ast_runtime*,_Enddef_Return*);
extern size_t _Enddef_Return_get_size(ast_runtime*,_Enddef_Return*);

struct Sync {
    int32_t ncid;
};


extern ast_err Sync_write(ast_runtime*,Sync*);
extern ast_err Sync_read(ast_runtime*,Sync**);
extern ast_err Sync_reclaim(ast_runtime*,Sync*);
extern size_t Sync_get_size(ast_runtime*,Sync*);

struct Sync_Return {
    int32_t ncstatus;
};


extern ast_err Sync_Return_write(ast_runtime*,Sync_Return*);
extern ast_err Sync_Return_read(ast_runtime*,Sync_Return**);
extern ast_err Sync_Return_reclaim(ast_runtime*,Sync_Return*);
extern size_t Sync_Return_get_size(ast_runtime*,Sync_Return*);

struct Abort {
    int32_t ncid;
};


extern ast_err Abort_write(ast_runtime*,Abort*);
extern ast_err Abort_read(ast_runtime*,Abort**);
extern ast_err Abort_reclaim(ast_runtime*,Abort*);
extern size_t Abort_get_size(ast_runtime*,Abort*);

struct Abort_Return {
    int32_t ncstatus;
};


extern ast_err Abort_Return_write(ast_runtime*,Abort_Return*);
extern ast_err Abort_Return_read(ast_runtime*,Abort_Return**);
extern ast_err Abort_Return_reclaim(ast_runtime*,Abort_Return*);
extern size_t Abort_Return_get_size(ast_runtime*,Abort_Return*);

struct Close {
    int32_t ncid;
};


extern ast_err Close_write(ast_runtime*,Close*);
extern ast_err Close_read(ast_runtime*,Close**);
extern ast_err Close_reclaim(ast_runtime*,Close*);
extern size_t Close_get_size(ast_runtime*,Close*);

struct Close_Return {
    int32_t ncstatus;
};


extern ast_err Close_Return_write(ast_runtime*,Close_Return*);
extern ast_err Close_Return_read(ast_runtime*,Close_Return**);
extern ast_err Close_Return_reclaim(ast_runtime*,Close_Return*);
extern size_t Close_Return_get_size(ast_runtime*,Close_Return*);

struct Set_fill {
    int32_t ncid;
    int32_t fillmode;
};


extern ast_err Set_fill_write(ast_runtime*,Set_fill*);
extern ast_err Set_fill_read(ast_runtime*,Set_fill**);
extern ast_err Set_fill_reclaim(ast_runtime*,Set_fill*);
extern size_t Set_fill_get_size(ast_runtime*,Set_fill*);

struct Set_fill_Return {
    int32_t ncstatus;
    int32_t oldmode;
};


extern ast_err Set_fill_Return_write(ast_runtime*,Set_fill_Return*);
extern ast_err Set_fill_Return_read(ast_runtime*,Set_fill_Return**);
extern ast_err Set_fill_Return_reclaim(ast_runtime*,Set_fill_Return*);
extern size_t Set_fill_Return_get_size(ast_runtime*,Set_fill_Return*);

struct Inq_base_pe {
    int32_t ncid;
};


extern ast_err Inq_base_pe_write(ast_runtime*,Inq_base_pe*);
extern ast_err Inq_base_pe_read(ast_runtime*,Inq_base_pe**);
extern ast_err Inq_base_pe_reclaim(ast_runtime*,Inq_base_pe*);
extern size_t Inq_base_pe_get_size(ast_runtime*,Inq_base_pe*);

struct Inq_base_pe_Return {
    int32_t ncstatus;
    int32_t pe;
};


extern ast_err Inq_base_pe_Return_write(ast_runtime*,Inq_base_pe_Return*);
extern ast_err Inq_base_pe_Return_read(ast_runtime*,Inq_base_pe_Return**);
extern ast_err Inq_base_pe_Return_reclaim(ast_runtime*,Inq_base_pe_Return*);
extern size_t Inq_base_pe_Return_get_size(ast_runtime*,Inq_base_pe_Return*);

struct Set_base_pe {
    int32_t ncid;
    int32_t pe;
};


extern ast_err Set_base_pe_write(ast_runtime*,Set_base_pe*);
extern ast_err Set_base_pe_read(ast_runtime*,Set_base_pe**);
extern ast_err Set_base_pe_reclaim(ast_runtime*,Set_base_pe*);
extern size_t Set_base_pe_get_size(ast_runtime*,Set_base_pe*);

struct Set_base_pe_Return {
    int32_t ncstatus;
};


extern ast_err Set_base_pe_Return_write(ast_runtime*,Set_base_pe_Return*);
extern ast_err Set_base_pe_Return_read(ast_runtime*,Set_base_pe_Return**);
extern ast_err Set_base_pe_Return_reclaim(ast_runtime*,Set_base_pe_Return*);
extern size_t Set_base_pe_Return_get_size(ast_runtime*,Set_base_pe_Return*);

struct Inq_format {
    int32_t ncid;
};


extern ast_err Inq_format_write(ast_runtime*,Inq_format*);
extern ast_err Inq_format_read(ast_runtime*,Inq_format**);
extern ast_err Inq_format_reclaim(ast_runtime*,Inq_format*);
extern size_t Inq_format_get_size(ast_runtime*,Inq_format*);

struct Inq_format_Return {
    int32_t ncstatus;
    int32_t format;
};


extern ast_err Inq_format_Return_write(ast_runtime*,Inq_format_Return*);
extern ast_err Inq_format_Return_read(ast_runtime*,Inq_format_Return**);
extern ast_err Inq_format_Return_reclaim(ast_runtime*,Inq_format_Return*);
extern size_t Inq_format_Return_get_size(ast_runtime*,Inq_format_Return*);

struct Inq {
    int32_t ncid;
};


extern ast_err Inq_write(ast_runtime*,Inq*);
extern ast_err Inq_read(ast_runtime*,Inq**);
extern ast_err Inq_reclaim(ast_runtime*,Inq*);
extern size_t Inq_get_size(ast_runtime*,Inq*);

struct Inq_Return {
    int32_t ncstatus;
    int32_t ndims;
    int32_t nvars;
    int32_t natts;
    int32_t unlimdimid;
};


extern ast_err Inq_Return_write(ast_runtime*,Inq_Return*);
extern ast_err Inq_Return_read(ast_runtime*,Inq_Return**);
extern ast_err Inq_Return_reclaim(ast_runtime*,Inq_Return*);
extern size_t Inq_Return_get_size(ast_runtime*,Inq_Return*);

struct Inq_type {
    int32_t ncid;
    int32_t xtype;
};


extern ast_err Inq_type_write(ast_runtime*,Inq_type*);
extern ast_err Inq_type_read(ast_runtime*,Inq_type**);
extern ast_err Inq_type_reclaim(ast_runtime*,Inq_type*);
extern size_t Inq_type_get_size(ast_runtime*,Inq_type*);

struct Inq_type_Return {
    int32_t ncstatus;
    char* name;
    uint64_t size;
};


extern ast_err Inq_type_Return_write(ast_runtime*,Inq_type_Return*);
extern ast_err Inq_type_Return_read(ast_runtime*,Inq_type_Return**);
extern ast_err Inq_type_Return_reclaim(ast_runtime*,Inq_type_Return*);
extern size_t Inq_type_Return_get_size(ast_runtime*,Inq_type_Return*);

struct Def_dim {
    int32_t ncid;
    char* name;
    uint64_t len;
};


extern ast_err Def_dim_write(ast_runtime*,Def_dim*);
extern ast_err Def_dim_read(ast_runtime*,Def_dim**);
extern ast_err Def_dim_reclaim(ast_runtime*,Def_dim*);
extern size_t Def_dim_get_size(ast_runtime*,Def_dim*);

struct Def_dim_Return {
    int32_t ncstatus;
    int32_t dimid;
};


extern ast_err Def_dim_Return_write(ast_runtime*,Def_dim_Return*);
extern ast_err Def_dim_Return_read(ast_runtime*,Def_dim_Return**);
extern ast_err Def_dim_Return_reclaim(ast_runtime*,Def_dim_Return*);
extern size_t Def_dim_Return_get_size(ast_runtime*,Def_dim_Return*);

struct Inq_dimid {
    int32_t ncid;
    char* name;
};


extern ast_err Inq_dimid_write(ast_runtime*,Inq_dimid*);
extern ast_err Inq_dimid_read(ast_runtime*,Inq_dimid**);
extern ast_err Inq_dimid_reclaim(ast_runtime*,Inq_dimid*);
extern size_t Inq_dimid_get_size(ast_runtime*,Inq_dimid*);

struct Inq_dimid_Return {
    int32_t ncstatus;
    int32_t dimid;
};


extern ast_err Inq_dimid_Return_write(ast_runtime*,Inq_dimid_Return*);
extern ast_err Inq_dimid_Return_read(ast_runtime*,Inq_dimid_Return**);
extern ast_err Inq_dimid_Return_reclaim(ast_runtime*,Inq_dimid_Return*);
extern size_t Inq_dimid_Return_get_size(ast_runtime*,Inq_dimid_Return*);

struct Inq_dim {
    int32_t ncid;
    int32_t dimid;
};


extern ast_err Inq_dim_write(ast_runtime*,Inq_dim*);
extern ast_err Inq_dim_read(ast_runtime*,Inq_dim**);
extern ast_err Inq_dim_reclaim(ast_runtime*,Inq_dim*);
extern size_t Inq_dim_get_size(ast_runtime*,Inq_dim*);

struct Inq_dim_Return {
    int32_t ncstatus;
    char* name;
    uint64_t len;
};


extern ast_err Inq_dim_Return_write(ast_runtime*,Inq_dim_Return*);
extern ast_err Inq_dim_Return_read(ast_runtime*,Inq_dim_Return**);
extern ast_err Inq_dim_Return_reclaim(ast_runtime*,Inq_dim_Return*);
extern size_t Inq_dim_Return_get_size(ast_runtime*,Inq_dim_Return*);

struct Inq_unlimdim {
    int32_t ncid;
};


extern ast_err Inq_unlimdim_write(ast_runtime*,Inq_unlimdim*);
extern ast_err Inq_unlimdim_read(ast_runtime*,Inq_unlimdim**);
extern ast_err Inq_unlimdim_reclaim(ast_runtime*,Inq_unlimdim*);
extern size_t Inq_unlimdim_get_size(ast_runtime*,Inq_unlimdim*);

struct Inq_unlimdim_Return {
    int32_t ncstatus;
    int32_t unlimdimid;
};


extern ast_err Inq_unlimdim_Return_write(ast_runtime*,Inq_unlimdim_Return*);
extern ast_err Inq_unlimdim_Return_read(ast_runtime*,Inq_unlimdim_Return**);
extern ast_err Inq_unlimdim_Return_reclaim(ast_runtime*,Inq_unlimdim_Return*);
extern size_t Inq_unlimdim_Return_get_size(ast_runtime*,Inq_unlimdim_Return*);

struct Rename_dim {
    int32_t ncid;
    int32_t dimid;
    char* name;
};


extern ast_err Rename_dim_write(ast_runtime*,Rename_dim*);
extern ast_err Rename_dim_read(ast_runtime*,Rename_dim**);
extern ast_err Rename_dim_reclaim(ast_runtime*,Rename_dim*);
extern size_t Rename_dim_get_size(ast_runtime*,Rename_dim*);

struct Rename_dim_Return {
    int32_t ncstatus;
};


extern ast_err Rename_dim_Return_write(ast_runtime*,Rename_dim_Return*);
extern ast_err Rename_dim_Return_read(ast_runtime*,Rename_dim_Return**);
extern ast_err Rename_dim_Return_reclaim(ast_runtime*,Rename_dim_Return*);
extern size_t Rename_dim_Return_get_size(ast_runtime*,Rename_dim_Return*);

struct Inq_att {
    int32_t ncid;
    int32_t varid;
    char* name;
};


extern ast_err Inq_att_write(ast_runtime*,Inq_att*);
extern ast_err Inq_att_read(ast_runtime*,Inq_att**);
extern ast_err Inq_att_reclaim(ast_runtime*,Inq_att*);
extern size_t Inq_att_get_size(ast_runtime*,Inq_att*);

struct Inq_att_Return {
    int32_t ncstatus;
    int32_t xtype;
    uint64_t len;
};


extern ast_err Inq_att_Return_write(ast_runtime*,Inq_att_Return*);
extern ast_err Inq_att_Return_read(ast_runtime*,Inq_att_Return**);
extern ast_err Inq_att_Return_reclaim(ast_runtime*,Inq_att_Return*);
extern size_t Inq_att_Return_get_size(ast_runtime*,Inq_att_Return*);

struct Inq_attid {
    int32_t ncid;
    int32_t varid;
    char* name;
};


extern ast_err Inq_attid_write(ast_runtime*,Inq_attid*);
extern ast_err Inq_attid_read(ast_runtime*,Inq_attid**);
extern ast_err Inq_attid_reclaim(ast_runtime*,Inq_attid*);
extern size_t Inq_attid_get_size(ast_runtime*,Inq_attid*);

struct Inq_attid_Return {
    int32_t ncstatus;
    int32_t attid;
};


extern ast_err Inq_attid_Return_write(ast_runtime*,Inq_attid_Return*);
extern ast_err Inq_attid_Return_read(ast_runtime*,Inq_attid_Return**);
extern ast_err Inq_attid_Return_reclaim(ast_runtime*,Inq_attid_Return*);
extern size_t Inq_attid_Return_get_size(ast_runtime*,Inq_attid_Return*);

struct Inq_attname {
    int32_t ncid;
    int32_t varid;
    int32_t attnum;
};


extern ast_err Inq_attname_write(ast_runtime*,Inq_attname*);
extern ast_err Inq_attname_read(ast_runtime*,Inq_attname**);
extern ast_err Inq_attname_reclaim(ast_runtime*,Inq_attname*);
extern size_t Inq_attname_get_size(ast_runtime*,Inq_attname*);

struct Inq_attname_Return {
    int32_t ncstatus;
    char* name;
};


extern ast_err Inq_attname_Return_write(ast_runtime*,Inq_attname_Return*);
extern ast_err Inq_attname_Return_read(ast_runtime*,Inq_attname_Return**);
extern ast_err Inq_attname_Return_reclaim(ast_runtime*,Inq_attname_Return*);
extern size_t Inq_attname_Return_get_size(ast_runtime*,Inq_attname_Return*);

struct Rename_att {
    int32_t ncid;
    int32_t varid;
    char* name;
    char* newname;
};


extern ast_err Rename_att_write(ast_runtime*,Rename_att*);
extern ast_err Rename_att_read(ast_runtime*,Rename_att**);
extern ast_err Rename_att_reclaim(ast_runtime*,Rename_att*);
extern size_t Rename_att_get_size(ast_runtime*,Rename_att*);

struct Rename_att_Return {
    int32_t ncstatus;
};


extern ast_err Rename_att_Return_write(ast_runtime*,Rename_att_Return*);
extern ast_err Rename_att_Return_read(ast_runtime*,Rename_att_Return**);
extern ast_err Rename_att_Return_reclaim(ast_runtime*,Rename_att_Return*);
extern size_t Rename_att_Return_get_size(ast_runtime*,Rename_att_Return*);

struct Del_att {
    int32_t ncid;
    int32_t varid;
    char* name;
};


extern ast_err Del_att_write(ast_runtime*,Del_att*);
extern ast_err Del_att_read(ast_runtime*,Del_att**);
extern ast_err Del_att_reclaim(ast_runtime*,Del_att*);
extern size_t Del_att_get_size(ast_runtime*,Del_att*);

struct Del_att_Return {
    int32_t ncstatus;
};


extern ast_err Del_att_Return_write(ast_runtime*,Del_att_Return*);
extern ast_err Del_att_Return_read(ast_runtime*,Del_att_Return**);
extern ast_err Del_att_Return_reclaim(ast_runtime*,Del_att_Return*);
extern size_t Del_att_Return_get_size(ast_runtime*,Del_att_Return*);

struct Get_att {
    int32_t ncid;
    int32_t varid;
    char* name;
    int32_t xtype;
};


extern ast_err Get_att_write(ast_runtime*,Get_att*);
extern ast_err Get_att_read(ast_runtime*,Get_att**);
extern ast_err Get_att_reclaim(ast_runtime*,Get_att*);
extern size_t Get_att_get_size(ast_runtime*,Get_att*);

struct Get_att_Return {
    int32_t ncstatus;
    bytes_t values;
};


extern ast_err Get_att_Return_write(ast_runtime*,Get_att_Return*);
extern ast_err Get_att_Return_read(ast_runtime*,Get_att_Return**);
extern ast_err Get_att_Return_reclaim(ast_runtime*,Get_att_Return*);
extern size_t Get_att_Return_get_size(ast_runtime*,Get_att_Return*);

struct Put_att {
    int32_t ncid;
    int32_t varid;
    char* name;
    int32_t vtype;
    uint64_t nelems;
    bytes_t value;
    int32_t atype;
};


extern ast_err Put_att_write(ast_runtime*,Put_att*);
extern ast_err Put_att_read(ast_runtime*,Put_att**);
extern ast_err Put_att_reclaim(ast_runtime*,Put_att*);
extern size_t Put_att_get_size(ast_runtime*,Put_att*);

struct Put_att_Return {
    int32_t ncstatus;
};


extern ast_err Put_att_Return_write(ast_runtime*,Put_att_Return*);
extern ast_err Put_att_Return_read(ast_runtime*,Put_att_Return**);
extern ast_err Put_att_Return_reclaim(ast_runtime*,Put_att_Return*);
extern size_t Put_att_Return_get_size(ast_runtime*,Put_att_Return*);

struct Def_var {
    int32_t ncid;
    char* name;
    int32_t xtype;
    int32_t ndims;
    struct {size_t count; int32_t* values;} dimids;
};


extern ast_err Def_var_write(ast_runtime*,Def_var*);
extern ast_err Def_var_read(ast_runtime*,Def_var**);
extern ast_err Def_var_reclaim(ast_runtime*,Def_var*);
extern size_t Def_var_get_size(ast_runtime*,Def_var*);

struct Def_var_Return {
    int32_t ncstatus;
    int32_t varid;
};


extern ast_err Def_var_Return_write(ast_runtime*,Def_var_Return*);
extern ast_err Def_var_Return_read(ast_runtime*,Def_var_Return**);
extern ast_err Def_var_Return_reclaim(ast_runtime*,Def_var_Return*);
extern size_t Def_var_Return_get_size(ast_runtime*,Def_var_Return*);

struct Inq_varid {
    int32_t ncid;
    char* name;
};


extern ast_err Inq_varid_write(ast_runtime*,Inq_varid*);
extern ast_err Inq_varid_read(ast_runtime*,Inq_varid**);
extern ast_err Inq_varid_reclaim(ast_runtime*,Inq_varid*);
extern size_t Inq_varid_get_size(ast_runtime*,Inq_varid*);

struct Inq_varid_Return {
    int32_t ncstatus;
    int32_t varid;
};


extern ast_err Inq_varid_Return_write(ast_runtime*,Inq_varid_Return*);
extern ast_err Inq_varid_Return_read(ast_runtime*,Inq_varid_Return**);
extern ast_err Inq_varid_Return_reclaim(ast_runtime*,Inq_varid_Return*);
extern size_t Inq_varid_Return_get_size(ast_runtime*,Inq_varid_Return*);

struct Rename_var {
    int32_t ncid;
    int32_t varid;
    char* name;
};


extern ast_err Rename_var_write(ast_runtime*,Rename_var*);
extern ast_err Rename_var_read(ast_runtime*,Rename_var**);
extern ast_err Rename_var_reclaim(ast_runtime*,Rename_var*);
extern size_t Rename_var_get_size(ast_runtime*,Rename_var*);

struct Rename_var_Return {
    int32_t ncstatus;
};


extern ast_err Rename_var_Return_write(ast_runtime*,Rename_var_Return*);
extern ast_err Rename_var_Return_read(ast_runtime*,Rename_var_Return**);
extern ast_err Rename_var_Return_reclaim(ast_runtime*,Rename_var_Return*);
extern size_t Rename_var_Return_get_size(ast_runtime*,Rename_var_Return*);

struct Get_vara {
    int32_t ncid;
    int32_t varid;
    struct {size_t count; uint64_t* values;} start;
    struct {size_t count; uint64_t* values;} edges;
    int32_t memtype;
};


extern ast_err Get_vara_write(ast_runtime*,Get_vara*);
extern ast_err Get_vara_read(ast_runtime*,Get_vara**);
extern ast_err Get_vara_reclaim(ast_runtime*,Get_vara*);
extern size_t Get_vara_get_size(ast_runtime*,Get_vara*);

struct Get_vara_Return {
    int32_t ncstatus;
    bytes_t value;
};


extern ast_err Get_vara_Return_write(ast_runtime*,Get_vara_Return*);
extern ast_err Get_vara_Return_read(ast_runtime*,Get_vara_Return**);
extern ast_err Get_vara_Return_reclaim(ast_runtime*,Get_vara_Return*);
extern size_t Get_vara_Return_get_size(ast_runtime*,Get_vara_Return*);

struct Put_vara {
    int32_t ncid;
    int32_t varid;
    struct {size_t count; uint64_t* values;} start;
    struct {size_t count; uint64_t* values;} edges;
    bytes_t value;
    int32_t memtype;
};


extern ast_err Put_vara_write(ast_runtime*,Put_vara*);
extern ast_err Put_vara_read(ast_runtime*,Put_vara**);
extern ast_err Put_vara_reclaim(ast_runtime*,Put_vara*);
extern size_t Put_vara_get_size(ast_runtime*,Put_vara*);

struct Put_vara_Return {
    int32_t ncstatus;
};


extern ast_err Put_vara_Return_write(ast_runtime*,Put_vara_Return*);
extern ast_err Put_vara_Return_read(ast_runtime*,Put_vara_Return**);
extern ast_err Put_vara_Return_reclaim(ast_runtime*,Put_vara_Return*);
extern size_t Put_vara_Return_get_size(ast_runtime*,Put_vara_Return*);

struct Get_vars {
    int32_t ncid;
    int32_t varid;
    struct {size_t count; uint64_t* values;} start;
    struct {size_t count; uint64_t* values;} edges;
    struct {size_t count; uint64_t* values;} stride;
    int32_t memtype;
};


extern ast_err Get_vars_write(ast_runtime*,Get_vars*);
extern ast_err Get_vars_read(ast_runtime*,Get_vars**);
extern ast_err Get_vars_reclaim(ast_runtime*,Get_vars*);
extern size_t Get_vars_get_size(ast_runtime*,Get_vars*);

struct Get_vars_Return {
    int32_t ncstatus;
    bytes_t value;
};


extern ast_err Get_vars_Return_write(ast_runtime*,Get_vars_Return*);
extern ast_err Get_vars_Return_read(ast_runtime*,Get_vars_Return**);
extern ast_err Get_vars_Return_reclaim(ast_runtime*,Get_vars_Return*);
extern size_t Get_vars_Return_get_size(ast_runtime*,Get_vars_Return*);

struct Put_vars {
    int32_t ncid;
    int32_t varid;
    struct {size_t count; uint64_t* values;} start;
    struct {size_t count; uint64_t* values;} edges;
    struct {size_t count; uint64_t* values;} stride;
    bytes_t value;
    int32_t memtype;
};


extern ast_err Put_vars_write(ast_runtime*,Put_vars*);
extern ast_err Put_vars_read(ast_runtime*,Put_vars**);
extern ast_err Put_vars_reclaim(ast_runtime*,Put_vars*);
extern size_t Put_vars_get_size(ast_runtime*,Put_vars*);

struct Put_vars_Return {
    int32_t ncstatus;
};


extern ast_err Put_vars_Return_write(ast_runtime*,Put_vars_Return*);
extern ast_err Put_vars_Return_read(ast_runtime*,Put_vars_Return**);
extern ast_err Put_vars_Return_reclaim(ast_runtime*,Put_vars_Return*);
extern size_t Put_vars_Return_get_size(ast_runtime*,Put_vars_Return*);

struct Get_varm {
    int32_t ncid;
    int32_t varid;
    struct {size_t count; uint64_t* values;} start;
    struct {size_t count; uint64_t* values;} edges;
    struct {size_t count; uint64_t* values;} stride;
    struct {size_t count; uint64_t* values;} imap;
    int32_t memtype;
};


extern ast_err Get_varm_write(ast_runtime*,Get_varm*);
extern ast_err Get_varm_read(ast_runtime*,Get_varm**);
extern ast_err Get_varm_reclaim(ast_runtime*,Get_varm*);
extern size_t Get_varm_get_size(ast_runtime*,Get_varm*);

struct Get_varm_Return {
    int32_t ncstatus;
    bytes_t value;
};


extern ast_err Get_varm_Return_write(ast_runtime*,Get_varm_Return*);
extern ast_err Get_varm_Return_read(ast_runtime*,Get_varm_Return**);
extern ast_err Get_varm_Return_reclaim(ast_runtime*,Get_varm_Return*);
extern size_t Get_varm_Return_get_size(ast_runtime*,Get_varm_Return*);

struct Put_varm {
    int32_t ncid;
    int32_t varid;
    struct {size_t count; uint64_t* values;} start;
    struct {size_t count; uint64_t* values;} edges;
    struct {size_t count; uint64_t* values;} stride;
    struct {size_t count; uint64_t* values;} imap;
    bytes_t value;
    int32_t memtype;
};


extern ast_err Put_varm_write(ast_runtime*,Put_varm*);
extern ast_err Put_varm_read(ast_runtime*,Put_varm**);
extern ast_err Put_varm_reclaim(ast_runtime*,Put_varm*);
extern size_t Put_varm_get_size(ast_runtime*,Put_varm*);

struct Put_varm_Return {
    int32_t ncstatus;
};


extern ast_err Put_varm_Return_write(ast_runtime*,Put_varm_Return*);
extern ast_err Put_varm_Return_read(ast_runtime*,Put_varm_Return**);
extern ast_err Put_varm_Return_reclaim(ast_runtime*,Put_varm_Return*);
extern size_t Put_varm_Return_get_size(ast_runtime*,Put_varm_Return*);

struct Inq_var_all {
    int32_t ncid;
    int32_t varid;
    char* name;
};


extern ast_err Inq_var_all_write(ast_runtime*,Inq_var_all*);
extern ast_err Inq_var_all_read(ast_runtime*,Inq_var_all**);
extern ast_err Inq_var_all_reclaim(ast_runtime*,Inq_var_all*);
extern size_t Inq_var_all_get_size(ast_runtime*,Inq_var_all*);

struct Inq_var_all_Return {
    int32_t ncstatus;
    int32_t xtype;
    int32_t ndims;
    struct {size_t count; int32_t* values;} dimids;
    int32_t natts;
    bool_t shuffle;
    bool_t deflate;
    int32_t deflate_level;
    bool_t fletcher32;
    bool_t contiguous;
    struct {size_t count; uint64_t* values;} chunksizes;
    bool_t no_fill;
    bytes_t fill_value;
    bool_t endianness;
    int32_t options_mask;
    int32_t pixels_per_block;
};


extern ast_err Inq_var_all_Return_write(ast_runtime*,Inq_var_all_Return*);
extern ast_err Inq_var_all_Return_read(ast_runtime*,Inq_var_all_Return**);
extern ast_err Inq_var_all_Return_reclaim(ast_runtime*,Inq_var_all_Return*);
extern size_t Inq_var_all_Return_get_size(ast_runtime*,Inq_var_all_Return*);

struct Show_metadata {
    int32_t ncid;
};


extern ast_err Show_metadata_write(ast_runtime*,Show_metadata*);
extern ast_err Show_metadata_read(ast_runtime*,Show_metadata**);
extern ast_err Show_metadata_reclaim(ast_runtime*,Show_metadata*);
extern size_t Show_metadata_get_size(ast_runtime*,Show_metadata*);

struct Show_metadata_Return {
    int32_t ncstatus;
};


extern ast_err Show_metadata_Return_write(ast_runtime*,Show_metadata_Return*);
extern ast_err Show_metadata_Return_read(ast_runtime*,Show_metadata_Return**);
extern ast_err Show_metadata_Return_reclaim(ast_runtime*,Show_metadata_Return*);
extern size_t Show_metadata_Return_get_size(ast_runtime*,Show_metadata_Return*);

struct Inq_unlimdims {
    int32_t ncid;
};


extern ast_err Inq_unlimdims_write(ast_runtime*,Inq_unlimdims*);
extern ast_err Inq_unlimdims_read(ast_runtime*,Inq_unlimdims**);
extern ast_err Inq_unlimdims_reclaim(ast_runtime*,Inq_unlimdims*);
extern size_t Inq_unlimdims_get_size(ast_runtime*,Inq_unlimdims*);

struct Inq_unlimdims_Return {
    int32_t ncstatus;
    int32_t nunlimdims;
    struct {size_t count; int32_t* values;} unlimdimids;
};


extern ast_err Inq_unlimdims_Return_write(ast_runtime*,Inq_unlimdims_Return*);
extern ast_err Inq_unlimdims_Return_read(ast_runtime*,Inq_unlimdims_Return**);
extern ast_err Inq_unlimdims_Return_reclaim(ast_runtime*,Inq_unlimdims_Return*);
extern size_t Inq_unlimdims_Return_get_size(ast_runtime*,Inq_unlimdims_Return*);

struct Var_par_access {
    int32_t ncid;
    int32_t varid;
    bool_t par_access;
};


extern ast_err Var_par_access_write(ast_runtime*,Var_par_access*);
extern ast_err Var_par_access_read(ast_runtime*,Var_par_access**);
extern ast_err Var_par_access_reclaim(ast_runtime*,Var_par_access*);
extern size_t Var_par_access_get_size(ast_runtime*,Var_par_access*);

struct Var_par_access_Return {
    int32_t ncstatus;
};


extern ast_err Var_par_access_Return_write(ast_runtime*,Var_par_access_Return*);
extern ast_err Var_par_access_Return_read(ast_runtime*,Var_par_access_Return**);
extern ast_err Var_par_access_Return_reclaim(ast_runtime*,Var_par_access_Return*);
extern size_t Var_par_access_Return_get_size(ast_runtime*,Var_par_access_Return*);

struct Inq_ncid {
    int32_t ncid;
    char* group;
};


extern ast_err Inq_ncid_write(ast_runtime*,Inq_ncid*);
extern ast_err Inq_ncid_read(ast_runtime*,Inq_ncid**);
extern ast_err Inq_ncid_reclaim(ast_runtime*,Inq_ncid*);
extern size_t Inq_ncid_get_size(ast_runtime*,Inq_ncid*);

struct Inq_ncid_Return {
    int32_t ncstatus;
    int32_t grp_ncid;
};


extern ast_err Inq_ncid_Return_write(ast_runtime*,Inq_ncid_Return*);
extern ast_err Inq_ncid_Return_read(ast_runtime*,Inq_ncid_Return**);
extern ast_err Inq_ncid_Return_reclaim(ast_runtime*,Inq_ncid_Return*);
extern size_t Inq_ncid_Return_get_size(ast_runtime*,Inq_ncid_Return*);

struct Inq_grps {
    int32_t ncid;
};


extern ast_err Inq_grps_write(ast_runtime*,Inq_grps*);
extern ast_err Inq_grps_read(ast_runtime*,Inq_grps**);
extern ast_err Inq_grps_reclaim(ast_runtime*,Inq_grps*);
extern size_t Inq_grps_get_size(ast_runtime*,Inq_grps*);

struct Inq_grps_Return {
    int32_t ncstatus;
    int32_t ngroups;
    struct {size_t count; int32_t* values;} ncids;
};


extern ast_err Inq_grps_Return_write(ast_runtime*,Inq_grps_Return*);
extern ast_err Inq_grps_Return_read(ast_runtime*,Inq_grps_Return**);
extern ast_err Inq_grps_Return_reclaim(ast_runtime*,Inq_grps_Return*);
extern size_t Inq_grps_Return_get_size(ast_runtime*,Inq_grps_Return*);

struct Inq_grpname {
    int32_t ncid;
};


extern ast_err Inq_grpname_write(ast_runtime*,Inq_grpname*);
extern ast_err Inq_grpname_read(ast_runtime*,Inq_grpname**);
extern ast_err Inq_grpname_reclaim(ast_runtime*,Inq_grpname*);
extern size_t Inq_grpname_get_size(ast_runtime*,Inq_grpname*);

struct Inq_grpname_Return {
    int32_t ncstatus;
    char* name;
};


extern ast_err Inq_grpname_Return_write(ast_runtime*,Inq_grpname_Return*);
extern ast_err Inq_grpname_Return_read(ast_runtime*,Inq_grpname_Return**);
extern ast_err Inq_grpname_Return_reclaim(ast_runtime*,Inq_grpname_Return*);
extern size_t Inq_grpname_Return_get_size(ast_runtime*,Inq_grpname_Return*);

struct Inq_grpname_full {
    int32_t ncid;
};


extern ast_err Inq_grpname_full_write(ast_runtime*,Inq_grpname_full*);
extern ast_err Inq_grpname_full_read(ast_runtime*,Inq_grpname_full**);
extern ast_err Inq_grpname_full_reclaim(ast_runtime*,Inq_grpname_full*);
extern size_t Inq_grpname_full_get_size(ast_runtime*,Inq_grpname_full*);

struct Inq_grpname_full_Return {
    int32_t ncstatus;
    struct {size_t count; uint64_t* values;} len;
    char* fullname;
};


extern ast_err Inq_grpname_full_Return_write(ast_runtime*,Inq_grpname_full_Return*);
extern ast_err Inq_grpname_full_Return_read(ast_runtime*,Inq_grpname_full_Return**);
extern ast_err Inq_grpname_full_Return_reclaim(ast_runtime*,Inq_grpname_full_Return*);
extern size_t Inq_grpname_full_Return_get_size(ast_runtime*,Inq_grpname_full_Return*);

struct Inq_grp_parent {
    int32_t ncid;
};


extern ast_err Inq_grp_parent_write(ast_runtime*,Inq_grp_parent*);
extern ast_err Inq_grp_parent_read(ast_runtime*,Inq_grp_parent**);
extern ast_err Inq_grp_parent_reclaim(ast_runtime*,Inq_grp_parent*);
extern size_t Inq_grp_parent_get_size(ast_runtime*,Inq_grp_parent*);

struct Inq_grp_parent_Return {
    int32_t ncstatus;
    int32_t parentncid;
};


extern ast_err Inq_grp_parent_Return_write(ast_runtime*,Inq_grp_parent_Return*);
extern ast_err Inq_grp_parent_Return_read(ast_runtime*,Inq_grp_parent_Return**);
extern ast_err Inq_grp_parent_Return_reclaim(ast_runtime*,Inq_grp_parent_Return*);
extern size_t Inq_grp_parent_Return_get_size(ast_runtime*,Inq_grp_parent_Return*);

struct Inq_grp_full_ncid {
    int32_t ncid;
    char* fullname;
};


extern ast_err Inq_grp_full_ncid_write(ast_runtime*,Inq_grp_full_ncid*);
extern ast_err Inq_grp_full_ncid_read(ast_runtime*,Inq_grp_full_ncid**);
extern ast_err Inq_grp_full_ncid_reclaim(ast_runtime*,Inq_grp_full_ncid*);
extern size_t Inq_grp_full_ncid_get_size(ast_runtime*,Inq_grp_full_ncid*);

struct Inq_grp_full_ncid_Return {
    int32_t ncstatus;
    int32_t groupncid;
};


extern ast_err Inq_grp_full_ncid_Return_write(ast_runtime*,Inq_grp_full_ncid_Return*);
extern ast_err Inq_grp_full_ncid_Return_read(ast_runtime*,Inq_grp_full_ncid_Return**);
extern ast_err Inq_grp_full_ncid_Return_reclaim(ast_runtime*,Inq_grp_full_ncid_Return*);
extern size_t Inq_grp_full_ncid_Return_get_size(ast_runtime*,Inq_grp_full_ncid_Return*);

struct Inq_varids {
    int32_t ncid;
};


extern ast_err Inq_varids_write(ast_runtime*,Inq_varids*);
extern ast_err Inq_varids_read(ast_runtime*,Inq_varids**);
extern ast_err Inq_varids_reclaim(ast_runtime*,Inq_varids*);
extern size_t Inq_varids_get_size(ast_runtime*,Inq_varids*);

struct Inq_varids_Return {
    int32_t ncstatus;
    int32_t nvars;
    struct {size_t count; int32_t* values;} varids;
};


extern ast_err Inq_varids_Return_write(ast_runtime*,Inq_varids_Return*);
extern ast_err Inq_varids_Return_read(ast_runtime*,Inq_varids_Return**);
extern ast_err Inq_varids_Return_reclaim(ast_runtime*,Inq_varids_Return*);
extern size_t Inq_varids_Return_get_size(ast_runtime*,Inq_varids_Return*);

struct Inq_dimids {
    int32_t ncid;
    bool_t includeparents;
};


extern ast_err Inq_dimids_write(ast_runtime*,Inq_dimids*);
extern ast_err Inq_dimids_read(ast_runtime*,Inq_dimids**);
extern ast_err Inq_dimids_reclaim(ast_runtime*,Inq_dimids*);
extern size_t Inq_dimids_get_size(ast_runtime*,Inq_dimids*);

struct Inq_dimids_Return {
    int32_t ncstatus;
    int32_t ndims;
    struct {size_t count; int32_t* values;} dimids;
};


extern ast_err Inq_dimids_Return_write(ast_runtime*,Inq_dimids_Return*);
extern ast_err Inq_dimids_Return_read(ast_runtime*,Inq_dimids_Return**);
extern ast_err Inq_dimids_Return_reclaim(ast_runtime*,Inq_dimids_Return*);
extern size_t Inq_dimids_Return_get_size(ast_runtime*,Inq_dimids_Return*);

struct Inq_typeids {
    int32_t ncid;
};


extern ast_err Inq_typeids_write(ast_runtime*,Inq_typeids*);
extern ast_err Inq_typeids_read(ast_runtime*,Inq_typeids**);
extern ast_err Inq_typeids_reclaim(ast_runtime*,Inq_typeids*);
extern size_t Inq_typeids_get_size(ast_runtime*,Inq_typeids*);

struct Inq_typeids_Return {
    int32_t ncstatus;
    int32_t ntypes;
    struct {size_t count; int32_t* values;} typeids;
};


extern ast_err Inq_typeids_Return_write(ast_runtime*,Inq_typeids_Return*);
extern ast_err Inq_typeids_Return_read(ast_runtime*,Inq_typeids_Return**);
extern ast_err Inq_typeids_Return_reclaim(ast_runtime*,Inq_typeids_Return*);
extern size_t Inq_typeids_Return_get_size(ast_runtime*,Inq_typeids_Return*);

struct Inq_type_equal {
    int32_t ncid1;
    int32_t typeid1;
    int32_t ncid2;
    int32_t typeid2;
};


extern ast_err Inq_type_equal_write(ast_runtime*,Inq_type_equal*);
extern ast_err Inq_type_equal_read(ast_runtime*,Inq_type_equal**);
extern ast_err Inq_type_equal_reclaim(ast_runtime*,Inq_type_equal*);
extern size_t Inq_type_equal_get_size(ast_runtime*,Inq_type_equal*);

struct Inq_type_equal_Return {
    int32_t ncstatus;
    bool_t equal;
};


extern ast_err Inq_type_equal_Return_write(ast_runtime*,Inq_type_equal_Return*);
extern ast_err Inq_type_equal_Return_read(ast_runtime*,Inq_type_equal_Return**);
extern ast_err Inq_type_equal_Return_reclaim(ast_runtime*,Inq_type_equal_Return*);
extern size_t Inq_type_equal_Return_get_size(ast_runtime*,Inq_type_equal_Return*);

struct Def_grp {
    int32_t ncid;
    char* name;
};


extern ast_err Def_grp_write(ast_runtime*,Def_grp*);
extern ast_err Def_grp_read(ast_runtime*,Def_grp**);
extern ast_err Def_grp_reclaim(ast_runtime*,Def_grp*);
extern size_t Def_grp_get_size(ast_runtime*,Def_grp*);

struct Def_grp_Return {
    int32_t ncstatus;
    int32_t grpncid;
};


extern ast_err Def_grp_Return_write(ast_runtime*,Def_grp_Return*);
extern ast_err Def_grp_Return_read(ast_runtime*,Def_grp_Return**);
extern ast_err Def_grp_Return_reclaim(ast_runtime*,Def_grp_Return*);
extern size_t Def_grp_Return_get_size(ast_runtime*,Def_grp_Return*);

struct Inq_user_type {
    int32_t ncid;
    int32_t typeid;
};


extern ast_err Inq_user_type_write(ast_runtime*,Inq_user_type*);
extern ast_err Inq_user_type_read(ast_runtime*,Inq_user_type**);
extern ast_err Inq_user_type_reclaim(ast_runtime*,Inq_user_type*);
extern size_t Inq_user_type_get_size(ast_runtime*,Inq_user_type*);

struct Inq_user_type_Return {
    int32_t ncstatus;
    char* name;
    uint64_t size;
    int32_t basetype;
    uint64_t nfields;
    int32_t typeclass;
};


extern ast_err Inq_user_type_Return_write(ast_runtime*,Inq_user_type_Return*);
extern ast_err Inq_user_type_Return_read(ast_runtime*,Inq_user_type_Return**);
extern ast_err Inq_user_type_Return_reclaim(ast_runtime*,Inq_user_type_Return*);
extern size_t Inq_user_type_Return_get_size(ast_runtime*,Inq_user_type_Return*);

struct Inq_typeid {
    int32_t ncid;
    char* name;
};


extern ast_err Inq_typeid_write(ast_runtime*,Inq_typeid*);
extern ast_err Inq_typeid_read(ast_runtime*,Inq_typeid**);
extern ast_err Inq_typeid_reclaim(ast_runtime*,Inq_typeid*);
extern size_t Inq_typeid_get_size(ast_runtime*,Inq_typeid*);

struct Inq_typeid_Return {
    int32_t ncstatus;
    int32_t typeid;
};


extern ast_err Inq_typeid_Return_write(ast_runtime*,Inq_typeid_Return*);
extern ast_err Inq_typeid_Return_read(ast_runtime*,Inq_typeid_Return**);
extern ast_err Inq_typeid_Return_reclaim(ast_runtime*,Inq_typeid_Return*);
extern size_t Inq_typeid_Return_get_size(ast_runtime*,Inq_typeid_Return*);

struct Def_compound {
    int32_t ncid;
    uint64_t size;
    char* name;
};


extern ast_err Def_compound_write(ast_runtime*,Def_compound*);
extern ast_err Def_compound_read(ast_runtime*,Def_compound**);
extern ast_err Def_compound_reclaim(ast_runtime*,Def_compound*);
extern size_t Def_compound_get_size(ast_runtime*,Def_compound*);

struct Def_compound_Return {
    int32_t ncstatus;
    int32_t typeid;
};


extern ast_err Def_compound_Return_write(ast_runtime*,Def_compound_Return*);
extern ast_err Def_compound_Return_read(ast_runtime*,Def_compound_Return**);
extern ast_err Def_compound_Return_reclaim(ast_runtime*,Def_compound_Return*);
extern size_t Def_compound_Return_get_size(ast_runtime*,Def_compound_Return*);

struct Insert_compound {
    int32_t ncid;
    int32_t typeid;
    char* name;
    uint64_t offset;
    int32_t fieldtypeid;
};


extern ast_err Insert_compound_write(ast_runtime*,Insert_compound*);
extern ast_err Insert_compound_read(ast_runtime*,Insert_compound**);
extern ast_err Insert_compound_reclaim(ast_runtime*,Insert_compound*);
extern size_t Insert_compound_get_size(ast_runtime*,Insert_compound*);

struct Insert_compound_Return {
    int32_t ncstatus;
};


extern ast_err Insert_compound_Return_write(ast_runtime*,Insert_compound_Return*);
extern ast_err Insert_compound_Return_read(ast_runtime*,Insert_compound_Return**);
extern ast_err Insert_compound_Return_reclaim(ast_runtime*,Insert_compound_Return*);
extern size_t Insert_compound_Return_get_size(ast_runtime*,Insert_compound_Return*);

struct Insert_array_compound {
    int32_t ncid;
    int32_t typeid;
    char* name;
    uint64_t offset;
    int32_t fieldtypeid;
    int32_t ndims;
    struct {size_t count; int32_t* values;} dimsizes;
};


extern ast_err Insert_array_compound_write(ast_runtime*,Insert_array_compound*);
extern ast_err Insert_array_compound_read(ast_runtime*,Insert_array_compound**);
extern ast_err Insert_array_compound_reclaim(ast_runtime*,Insert_array_compound*);
extern size_t Insert_array_compound_get_size(ast_runtime*,Insert_array_compound*);

struct Insert_array_compound_Return {
    int32_t ncstatus;
};


extern ast_err Insert_array_compound_Return_write(ast_runtime*,Insert_array_compound_Return*);
extern ast_err Insert_array_compound_Return_read(ast_runtime*,Insert_array_compound_Return**);
extern ast_err Insert_array_compound_Return_reclaim(ast_runtime*,Insert_array_compound_Return*);
extern size_t Insert_array_compound_Return_get_size(ast_runtime*,Insert_array_compound_Return*);

struct Inq_compound_field {
    int32_t ncid;
    int32_t typeid;
    int32_t fieldid;
};


extern ast_err Inq_compound_field_write(ast_runtime*,Inq_compound_field*);
extern ast_err Inq_compound_field_read(ast_runtime*,Inq_compound_field**);
extern ast_err Inq_compound_field_reclaim(ast_runtime*,Inq_compound_field*);
extern size_t Inq_compound_field_get_size(ast_runtime*,Inq_compound_field*);

struct Inq_compound_field_Return {
    int32_t ncstatus;
    char* name;
    uint64_t offset;
    int32_t fieldtypeid;
    int32_t ndims;
    struct {size_t count; int32_t* values;} dimsizes;
};


extern ast_err Inq_compound_field_Return_write(ast_runtime*,Inq_compound_field_Return*);
extern ast_err Inq_compound_field_Return_read(ast_runtime*,Inq_compound_field_Return**);
extern ast_err Inq_compound_field_Return_reclaim(ast_runtime*,Inq_compound_field_Return*);
extern size_t Inq_compound_field_Return_get_size(ast_runtime*,Inq_compound_field_Return*);

struct Inq_compound_fieldindex {
    int32_t ncid;
    int32_t typeid;
    char* name;
};


extern ast_err Inq_compound_fieldindex_write(ast_runtime*,Inq_compound_fieldindex*);
extern ast_err Inq_compound_fieldindex_read(ast_runtime*,Inq_compound_fieldindex**);
extern ast_err Inq_compound_fieldindex_reclaim(ast_runtime*,Inq_compound_fieldindex*);
extern size_t Inq_compound_fieldindex_get_size(ast_runtime*,Inq_compound_fieldindex*);

struct Inq_compound_fieldindex_Return {
    int32_t ncstatus;
    int32_t fieldid;
};


extern ast_err Inq_compound_fieldindex_Return_write(ast_runtime*,Inq_compound_fieldindex_Return*);
extern ast_err Inq_compound_fieldindex_Return_read(ast_runtime*,Inq_compound_fieldindex_Return**);
extern ast_err Inq_compound_fieldindex_Return_reclaim(ast_runtime*,Inq_compound_fieldindex_Return*);
extern size_t Inq_compound_fieldindex_Return_get_size(ast_runtime*,Inq_compound_fieldindex_Return*);

struct Def_vlen {
    int32_t ncid;
    char* name;
    int32_t base_typeid;
};


extern ast_err Def_vlen_write(ast_runtime*,Def_vlen*);
extern ast_err Def_vlen_read(ast_runtime*,Def_vlen**);
extern ast_err Def_vlen_reclaim(ast_runtime*,Def_vlen*);
extern size_t Def_vlen_get_size(ast_runtime*,Def_vlen*);

struct Def_vlen_Return {
    int32_t ncstatus;
    int32_t typeid;
};


extern ast_err Def_vlen_Return_write(ast_runtime*,Def_vlen_Return*);
extern ast_err Def_vlen_Return_read(ast_runtime*,Def_vlen_Return**);
extern ast_err Def_vlen_Return_reclaim(ast_runtime*,Def_vlen_Return*);
extern size_t Def_vlen_Return_get_size(ast_runtime*,Def_vlen_Return*);

struct Put_vlen_element {
    int32_t ncid;
    int32_t typeid;
    bytes_t element;
    uint64_t len;
    bytes_t data;
};


extern ast_err Put_vlen_element_write(ast_runtime*,Put_vlen_element*);
extern ast_err Put_vlen_element_read(ast_runtime*,Put_vlen_element**);
extern ast_err Put_vlen_element_reclaim(ast_runtime*,Put_vlen_element*);
extern size_t Put_vlen_element_get_size(ast_runtime*,Put_vlen_element*);

struct Put_vlen_element_Return {
    int32_t ncstatus;
};


extern ast_err Put_vlen_element_Return_write(ast_runtime*,Put_vlen_element_Return*);
extern ast_err Put_vlen_element_Return_read(ast_runtime*,Put_vlen_element_Return**);
extern ast_err Put_vlen_element_Return_reclaim(ast_runtime*,Put_vlen_element_Return*);
extern size_t Put_vlen_element_Return_get_size(ast_runtime*,Put_vlen_element_Return*);

struct Get_vlen_element {
    int32_t ncid;
    int32_t typeid;
};


extern ast_err Get_vlen_element_write(ast_runtime*,Get_vlen_element*);
extern ast_err Get_vlen_element_read(ast_runtime*,Get_vlen_element**);
extern ast_err Get_vlen_element_reclaim(ast_runtime*,Get_vlen_element*);
extern size_t Get_vlen_element_get_size(ast_runtime*,Get_vlen_element*);

struct Get_vlen_element_Return {
    int32_t ncstatus;
    bytes_t element;
    uint64_t len;
    bytes_t data;
};


extern ast_err Get_vlen_element_Return_write(ast_runtime*,Get_vlen_element_Return*);
extern ast_err Get_vlen_element_Return_read(ast_runtime*,Get_vlen_element_Return**);
extern ast_err Get_vlen_element_Return_reclaim(ast_runtime*,Get_vlen_element_Return*);
extern size_t Get_vlen_element_Return_get_size(ast_runtime*,Get_vlen_element_Return*);

struct Def_enum {
    int32_t ncid;
    int32_t basetypeid;
    char* name;
};


extern ast_err Def_enum_write(ast_runtime*,Def_enum*);
extern ast_err Def_enum_read(ast_runtime*,Def_enum**);
extern ast_err Def_enum_reclaim(ast_runtime*,Def_enum*);
extern size_t Def_enum_get_size(ast_runtime*,Def_enum*);

struct Def_enum_Return {
    int32_t ncstatus;
    int32_t typeid;
};


extern ast_err Def_enum_Return_write(ast_runtime*,Def_enum_Return*);
extern ast_err Def_enum_Return_read(ast_runtime*,Def_enum_Return**);
extern ast_err Def_enum_Return_reclaim(ast_runtime*,Def_enum_Return*);
extern size_t Def_enum_Return_get_size(ast_runtime*,Def_enum_Return*);

struct Insert_enum {
    int32_t ncid;
    int32_t typeid;
    char* name;
    bytes_t value;
};


extern ast_err Insert_enum_write(ast_runtime*,Insert_enum*);
extern ast_err Insert_enum_read(ast_runtime*,Insert_enum**);
extern ast_err Insert_enum_reclaim(ast_runtime*,Insert_enum*);
extern size_t Insert_enum_get_size(ast_runtime*,Insert_enum*);

struct Insert_enum_Return {
    int32_t ncstatus;
};


extern ast_err Insert_enum_Return_write(ast_runtime*,Insert_enum_Return*);
extern ast_err Insert_enum_Return_read(ast_runtime*,Insert_enum_Return**);
extern ast_err Insert_enum_Return_reclaim(ast_runtime*,Insert_enum_Return*);
extern size_t Insert_enum_Return_get_size(ast_runtime*,Insert_enum_Return*);

struct Inq_enum_member {
    int32_t ncid;
    int32_t typeid;
    int32_t index;
};


extern ast_err Inq_enum_member_write(ast_runtime*,Inq_enum_member*);
extern ast_err Inq_enum_member_read(ast_runtime*,Inq_enum_member**);
extern ast_err Inq_enum_member_reclaim(ast_runtime*,Inq_enum_member*);
extern size_t Inq_enum_member_get_size(ast_runtime*,Inq_enum_member*);

struct Inq_enum_member_Return {
    int32_t ncstatus;
    char* name;
    bytes_t value;
};


extern ast_err Inq_enum_member_Return_write(ast_runtime*,Inq_enum_member_Return*);
extern ast_err Inq_enum_member_Return_read(ast_runtime*,Inq_enum_member_Return**);
extern ast_err Inq_enum_member_Return_reclaim(ast_runtime*,Inq_enum_member_Return*);
extern size_t Inq_enum_member_Return_get_size(ast_runtime*,Inq_enum_member_Return*);

struct Inq_enum_ident {
    int32_t ncid;
    int32_t typeid;
    uint64_t value;
};


extern ast_err Inq_enum_ident_write(ast_runtime*,Inq_enum_ident*);
extern ast_err Inq_enum_ident_read(ast_runtime*,Inq_enum_ident**);
extern ast_err Inq_enum_ident_reclaim(ast_runtime*,Inq_enum_ident*);
extern size_t Inq_enum_ident_get_size(ast_runtime*,Inq_enum_ident*);

struct Inq_enum_ident_Return {
    int32_t ncstatus;
    char* name;
};


extern ast_err Inq_enum_ident_Return_write(ast_runtime*,Inq_enum_ident_Return*);
extern ast_err Inq_enum_ident_Return_read(ast_runtime*,Inq_enum_ident_Return**);
extern ast_err Inq_enum_ident_Return_reclaim(ast_runtime*,Inq_enum_ident_Return*);
extern size_t Inq_enum_ident_Return_get_size(ast_runtime*,Inq_enum_ident_Return*);

struct Def_opaque {
    int32_t ncid;
    uint64_t size;
    char* name;
};


extern ast_err Def_opaque_write(ast_runtime*,Def_opaque*);
extern ast_err Def_opaque_read(ast_runtime*,Def_opaque**);
extern ast_err Def_opaque_reclaim(ast_runtime*,Def_opaque*);
extern size_t Def_opaque_get_size(ast_runtime*,Def_opaque*);

struct Def_opaque_Return {
    int32_t ncstatus;
    int32_t typeid;
};


extern ast_err Def_opaque_Return_write(ast_runtime*,Def_opaque_Return*);
extern ast_err Def_opaque_Return_read(ast_runtime*,Def_opaque_Return**);
extern ast_err Def_opaque_Return_reclaim(ast_runtime*,Def_opaque_Return*);
extern size_t Def_opaque_Return_get_size(ast_runtime*,Def_opaque_Return*);

struct Def_var_deflate {
    int32_t ncid;
    int32_t varid;
    bool_t shuffle;
    bool_t deflate;
    int32_t deflatelevel;
};


extern ast_err Def_var_deflate_write(ast_runtime*,Def_var_deflate*);
extern ast_err Def_var_deflate_read(ast_runtime*,Def_var_deflate**);
extern ast_err Def_var_deflate_reclaim(ast_runtime*,Def_var_deflate*);
extern size_t Def_var_deflate_get_size(ast_runtime*,Def_var_deflate*);

struct Def_var_deflate_Return {
    int32_t ncstatus;
};


extern ast_err Def_var_deflate_Return_write(ast_runtime*,Def_var_deflate_Return*);
extern ast_err Def_var_deflate_Return_read(ast_runtime*,Def_var_deflate_Return**);
extern ast_err Def_var_deflate_Return_reclaim(ast_runtime*,Def_var_deflate_Return*);
extern size_t Def_var_deflate_Return_get_size(ast_runtime*,Def_var_deflate_Return*);

struct Def_var_fletcher32 {
    int32_t ncid;
    int32_t varid;
    bool_t fletcher32;
};


extern ast_err Def_var_fletcher32_write(ast_runtime*,Def_var_fletcher32*);
extern ast_err Def_var_fletcher32_read(ast_runtime*,Def_var_fletcher32**);
extern ast_err Def_var_fletcher32_reclaim(ast_runtime*,Def_var_fletcher32*);
extern size_t Def_var_fletcher32_get_size(ast_runtime*,Def_var_fletcher32*);

struct Def_var_fletcher32_Return {
    int32_t ncstatus;
};


extern ast_err Def_var_fletcher32_Return_write(ast_runtime*,Def_var_fletcher32_Return*);
extern ast_err Def_var_fletcher32_Return_read(ast_runtime*,Def_var_fletcher32_Return**);
extern ast_err Def_var_fletcher32_Return_reclaim(ast_runtime*,Def_var_fletcher32_Return*);
extern size_t Def_var_fletcher32_Return_get_size(ast_runtime*,Def_var_fletcher32_Return*);

struct Def_var_chunking {
    int32_t ncid;
    int32_t varid;
    bool_t contiguous;
    struct {size_t count; uint64_t* values;} chunksizes;
};


extern ast_err Def_var_chunking_write(ast_runtime*,Def_var_chunking*);
extern ast_err Def_var_chunking_read(ast_runtime*,Def_var_chunking**);
extern ast_err Def_var_chunking_reclaim(ast_runtime*,Def_var_chunking*);
extern size_t Def_var_chunking_get_size(ast_runtime*,Def_var_chunking*);

struct Def_var_chunking_Return {
    int32_t ncstatus;
};


extern ast_err Def_var_chunking_Return_write(ast_runtime*,Def_var_chunking_Return*);
extern ast_err Def_var_chunking_Return_read(ast_runtime*,Def_var_chunking_Return**);
extern ast_err Def_var_chunking_Return_reclaim(ast_runtime*,Def_var_chunking_Return*);
extern size_t Def_var_chunking_Return_get_size(ast_runtime*,Def_var_chunking_Return*);

struct Def_var_fill {
    int32_t ncid;
    int32_t varid;
    bool_t nofill;
    bytes_t fill_value;
};


extern ast_err Def_var_fill_write(ast_runtime*,Def_var_fill*);
extern ast_err Def_var_fill_read(ast_runtime*,Def_var_fill**);
extern ast_err Def_var_fill_reclaim(ast_runtime*,Def_var_fill*);
extern size_t Def_var_fill_get_size(ast_runtime*,Def_var_fill*);

struct Def_var_fill_Return {
    int32_t ncstatus;
};


extern ast_err Def_var_fill_Return_write(ast_runtime*,Def_var_fill_Return*);
extern ast_err Def_var_fill_Return_read(ast_runtime*,Def_var_fill_Return**);
extern ast_err Def_var_fill_Return_reclaim(ast_runtime*,Def_var_fill_Return*);
extern size_t Def_var_fill_Return_get_size(ast_runtime*,Def_var_fill_Return*);

struct Def_var_endian {
    int32_t ncid;
    int32_t varid;
    bool_t bigendian;
};


extern ast_err Def_var_endian_write(ast_runtime*,Def_var_endian*);
extern ast_err Def_var_endian_read(ast_runtime*,Def_var_endian**);
extern ast_err Def_var_endian_reclaim(ast_runtime*,Def_var_endian*);
extern size_t Def_var_endian_get_size(ast_runtime*,Def_var_endian*);

struct Def_var_endian_Return {
    int32_t ncstatus;
};


extern ast_err Def_var_endian_Return_write(ast_runtime*,Def_var_endian_Return*);
extern ast_err Def_var_endian_Return_read(ast_runtime*,Def_var_endian_Return**);
extern ast_err Def_var_endian_Return_reclaim(ast_runtime*,Def_var_endian_Return*);
extern size_t Def_var_endian_Return_get_size(ast_runtime*,Def_var_endian_Return*);

struct Set_var_chunk_cache {
    int32_t ncid;
    int32_t varid;
    uint64_t size;
    uint64_t nelems;
    float preemption;
};


extern ast_err Set_var_chunk_cache_write(ast_runtime*,Set_var_chunk_cache*);
extern ast_err Set_var_chunk_cache_read(ast_runtime*,Set_var_chunk_cache**);
extern ast_err Set_var_chunk_cache_reclaim(ast_runtime*,Set_var_chunk_cache*);
extern size_t Set_var_chunk_cache_get_size(ast_runtime*,Set_var_chunk_cache*);

struct Set_var_chunk_cache_Return {
    int32_t ncstatus;
};


extern ast_err Set_var_chunk_cache_Return_write(ast_runtime*,Set_var_chunk_cache_Return*);
extern ast_err Set_var_chunk_cache_Return_read(ast_runtime*,Set_var_chunk_cache_Return**);
extern ast_err Set_var_chunk_cache_Return_reclaim(ast_runtime*,Set_var_chunk_cache_Return*);
extern size_t Set_var_chunk_cache_Return_get_size(ast_runtime*,Set_var_chunk_cache_Return*);

struct Get_var_chunk_cache {
    int32_t ncid;
    int32_t varid;
};


extern ast_err Get_var_chunk_cache_write(ast_runtime*,Get_var_chunk_cache*);
extern ast_err Get_var_chunk_cache_read(ast_runtime*,Get_var_chunk_cache**);
extern ast_err Get_var_chunk_cache_reclaim(ast_runtime*,Get_var_chunk_cache*);
extern size_t Get_var_chunk_cache_get_size(ast_runtime*,Get_var_chunk_cache*);

struct Get_var_chunk_cache_Return {
    int32_t ncstatus;
    uint64_t size;
    uint64_t nelems;
    float preemption;
};


extern ast_err Get_var_chunk_cache_Return_write(ast_runtime*,Get_var_chunk_cache_Return*);
extern ast_err Get_var_chunk_cache_Return_read(ast_runtime*,Get_var_chunk_cache_Return**);
extern ast_err Get_var_chunk_cache_Return_reclaim(ast_runtime*,Get_var_chunk_cache_Return*);
extern size_t Get_var_chunk_cache_Return_get_size(ast_runtime*,Get_var_chunk_cache_Return*);

struct NC_set_log_level {
    int32_t newlevel;
};


extern ast_err NC_set_log_level_write(ast_runtime*,NC_set_log_level*);
extern ast_err NC_set_log_level_read(ast_runtime*,NC_set_log_level**);
extern ast_err NC_set_log_level_reclaim(ast_runtime*,NC_set_log_level*);
extern size_t NC_set_log_level_get_size(ast_runtime*,NC_set_log_level*);

struct NC_set_log_level_Return {
    int32_t ncstatus;
};


extern ast_err NC_set_log_level_Return_write(ast_runtime*,NC_set_log_level_Return*);
extern ast_err NC_set_log_level_Return_read(ast_runtime*,NC_set_log_level_Return**);
extern ast_err NC_set_log_level_Return_reclaim(ast_runtime*,NC_set_log_level_Return*);
extern size_t NC_set_log_level_Return_get_size(ast_runtime*,NC_set_log_level_Return*);

struct NC_inq_libvers {
};


extern ast_err NC_inq_libvers_write(ast_runtime*,NC_inq_libvers*);
extern ast_err NC_inq_libvers_read(ast_runtime*,NC_inq_libvers**);
extern ast_err NC_inq_libvers_reclaim(ast_runtime*,NC_inq_libvers*);
extern size_t NC_inq_libvers_get_size(ast_runtime*,NC_inq_libvers*);

struct NC_inq_libvers_Return {
    char* version;
};


extern ast_err NC_inq_libvers_Return_write(ast_runtime*,NC_inq_libvers_Return*);
extern ast_err NC_inq_libvers_Return_read(ast_runtime*,NC_inq_libvers_Return**);
extern ast_err NC_inq_libvers_Return_reclaim(ast_runtime*,NC_inq_libvers_Return*);
extern size_t NC_inq_libvers_Return_get_size(ast_runtime*,NC_inq_libvers_Return*);

struct NC_delete_mp {
    char* path;
    int32_t basepe;
};


extern ast_err NC_delete_mp_write(ast_runtime*,NC_delete_mp*);
extern ast_err NC_delete_mp_read(ast_runtime*,NC_delete_mp**);
extern ast_err NC_delete_mp_reclaim(ast_runtime*,NC_delete_mp*);
extern size_t NC_delete_mp_get_size(ast_runtime*,NC_delete_mp*);

struct NC_delete_mp_Return {
    int32_t ncstatus;
};


extern ast_err NC_delete_mp_Return_write(ast_runtime*,NC_delete_mp_Return*);
extern ast_err NC_delete_mp_Return_read(ast_runtime*,NC_delete_mp_Return**);
extern ast_err NC_delete_mp_Return_reclaim(ast_runtime*,NC_delete_mp_Return*);
extern size_t NC_delete_mp_Return_get_size(ast_runtime*,NC_delete_mp_Return*);

#endif /*PROTORPC_H*/

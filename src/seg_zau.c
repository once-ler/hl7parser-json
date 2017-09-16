/**
* \file seg_zau.c
*
* Procedure authorization information segment (ZAU) accessors for the HL7 parser.
*
* \internal
* Copyright (c) 2011 Juan Jose Comellas <juanjo@comellas.org>
*
* \warning DO NOT MODIFY THIS FILE.
*
* Autogenerated by the ./hl7segdef.py script on Mon Jun  6 12:54:47 2011
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/segment.h>
#include <hl7parser/seg_zau.h>

BEGIN_C_DECL()

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_zau_prev_authorization_id( HL7_Segment *segment )
{
    return hl7_segment_component( segment, 0, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_prev_authorization_id( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 0, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_prev_authorization_id_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 0, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_zau_payor_control_id( HL7_Segment *segment )
{
    return hl7_segment_component( segment, 1, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_payor_control_id( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 1, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_payor_control_id_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 1, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_zau_authorization_status( HL7_Segment *segment )
{
    return hl7_segment_component( segment, 2, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_authorization_status( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 2, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_authorization_status_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 2, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_zau_authorization_status_text( HL7_Segment *segment )
{
    return hl7_segment_component( segment, 2, 1 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_authorization_status_text( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 2, 1, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_authorization_status_text_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 2, 1, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_zau_pre_authorization_id( HL7_Segment *segment )
{
    return hl7_segment_component( segment, 3, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_pre_authorization_id( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 3, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_pre_authorization_id_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 3, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_zau_pre_authorization_date( HL7_Segment *segment )
{
    return hl7_segment_field( segment, 4 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_pre_authorization_date( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_field( segment, 4, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_pre_authorization_date_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_field( segment, 4, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_zau_copay( HL7_Segment *segment )
{
    return hl7_segment_subcomponent( segment, 5, 0, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_copay( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_subcomponent( segment, 5, 0, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_copay_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_subcomponent( segment, 5, 0, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_zau_copay_currency( HL7_Segment *segment )
{
    return hl7_segment_subcomponent( segment, 5, 0, 1 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_copay_currency( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_subcomponent( segment, 5, 0, 1, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_zau_set_copay_currency_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_subcomponent( segment, 5, 0, 1, &element ) : rc );
}

END_C_DECL()
<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 org.erms.business.User"%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
<title>:: Sahana ::</title>
<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>
<body>

<jsp:include page="comman/header.inc"></jsp:include>
    <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">
   <%
       boolean isAuthenticated = false;
       if (request.getSession()==null){
           throw new Exception("Session expired!");
       }else if(request.getSession().getAttribute(ERMSConstants.IContextInfoConstants.USER_INFO)!=null){
           //user is already logged in. Do nothing
           isAuthenticated = true;
       }else {


       DataAccessManager dataAccessManager = new DataAccessManager();
       String username = request.getParameter("userName");
       String password = request.getParameter("password");

       User user = null;
       try {
           user = dataAccessManager.loginSuccess(username, password);
       } catch (Exception e) {
           throw new Exception("Problem in validating user");
       }
       if( !"".equals(username) && user != null) {
           request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.USER_INFO, user);
             isAuthenticated = true ;
       }else{
           isAuthenticated = false;
       }
       }

       if (isAuthenticated){
   %>

      <tr>
            <td width="134" valign="top"><img src="images/imgloginrqstms.jpg" width="302" height="200" border="0"></td>
            <td valign="top" bgcolor="#D8E9FD">
           <table width="760" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="34%" class="formText" >&nbsp;</td>
                <td width="66%"  >&nbsp;</td>
              </tr>
              <tr>
              <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                <td  nowrap class="formText" align="left" ><strong><a href="Add_Request.jsp" style="text-decoration:none"  class="style1">Add Request</a></strong> </td>
                </tr>
                <tr>
              <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                
                <td  nowrap class="formText" align="left" ><strong><a href="Search_Request.jsp?<%=ERMSConstants.ISearchConstants.SEARCH_REQUEST%>" style="text-decoration:none"  class="style1">Search Request</a></strong> </td>
                </tr>

                <tr>
                <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                <td  nowrap class="formText" align="left" ><strong>Reports</strong></td>
                </tr>
                <tr>
                <td  align="right" class="formText">&nbsp;&nbsp;&nbsp;&nbsp;&raquo;</strong></td>
                <td  nowrap class="formText" align="left" >&nbsp;&nbsp;&nbsp;<a href="/reports/sahana-report.vx?report=All-request-details-grouped-District"><strong>Request Detail Reports</strong></a></td>
                </tr>
                <tr>
                <td  align="right" class="formText">&nbsp;&nbsp;&nbsp;&nbsp;&raquo;</strong></td>
                <td  nowrap class="formText" align="left" >&nbsp;&nbsp;&nbsp;<a href="/reports/sahana-report.vx?report=fulfill-request-detail"><strong>Fulfillment Details Reports</strong></a></td>
                </tr>
              </table>

             </td>
              </tr>
           <% }else{

           %>
                <tr>
                <td class="formText" align="center" ><font size="2">Invalid Username / Password. Please <a href="Index.jsp">Try Again</a></font></td>
                <td >&nbsp;</td>
              </tr>


      <%}
       %>
      </table>

      <jsp:include page="comman/footer.inc"></jsp:include>
      </body>
</html>

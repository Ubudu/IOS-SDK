#
# Copyright (c) 2014, UBUDU SAS
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#         SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

class CustomHandlerController < ApplicationController

# Implementation of server callback for Ubudu uBeacon SDK grammar 
#
# @params format [Symbol] the format type, `:json`
# @params case [String] the test_case you want to test
# @return [JSON] the response a JSON object in the format that can be handled by the UbuduSDK.
# the format is a json containing {decision : "enable"|"disable"|"notify", optional_parameters (notify_user, open_url, open_pbk, data)}
# Example : /custom_handler/execute_callback?case=enable&data_type=beacon&id=3
  def execute_callback
    test_case = params[:case]
    response = Hash.new
    response[:version] = 3
    extra = {}
    err=false
    case test_case
    when "disable"
      #Simulate a decision to halt the execution of the action stored on the client. 
      response[:decision] = "disable"
    when "sms"
      response[:decision] = "disable"
      #Simulate a decision to halt the execution of the action stored on the client and trigger an action on the server i.e. sending an SMS
      #Now for instance trigger an SMS to be send or a push notification
      # Add your own implementation here
      #SmsHelper::send_sms("xxxxxxxx","Alerte VIP","xxx en magasin")
    when "enable"
      response[:decision] = "enable"
      if (params[:data_type] && params[:id])
        data_type=params[:data_type]
        case data_type
        when "geofence"
           #Simulate a decision to continue execution of the action but provide "fresh" data to the client to execute the action
           # Now get the stored informations on the geofence and return it back
           # Add your own implementation here
           # geofence = UGeofence.where(:id => params[:id]).first
           # response[:data] = geofence.as_json({:api_version => 2})
        when "beacon"
              #Simulate a decision to continue execution of the action but provide "fresh" data to the client to execute the action
             # Now get the stored informations on the beacon and return it back
             # Add your own implementation here
             #beacon = UBeacon.where(:id => params[:id]).first
             #response[:data] = beacon.as_json({:api_version => 2})
        end
      end
    when "notify_user"
       #Simulate a decision to overule locally stored actions with a simple notification message without custom payload
      # Add your own implementation here
      response[:notify_user] = "{\"alertBody\":\"This is a simple notification message\",\"payload\": {} }"
    when "open_url"
      response[:decision] = "notify"
      #Simulate a decision to overule locally stored actions with notification message following by the opening of an URL in a web-view
      # Add your own implementation here
      response[:notify_user] =  "{\"alertBody\":\"This is a notification redirecting to Yahoo\",\"payload\": {} }"
      response[:open_url] = "http://www.yahoo.com"
    when "open_pbk"
      response[:decision] = "notify"
      #Simulate a decision to overule locally stored actions with notification message following by the opening of a passbook indicated in a URL
      #Add your own implementation here
      response[:notify_user] = "{\"alertBody\":\"Benefit from a coupon\",\"payload\": {} }"
      response[:open_pbk] = "https://deals-images-eu-prod.s3.amazonaws.com/passbooks/atollesopticiens_passid73_coupon__ucodenone_2013-06-14.pkpass"
    when "err"
      #Simulate an error on the server
      #Add your own implementation here
      err=true
    end
    if (!err)
     respond_to do |format|
       # the format is a json containing {decision : "enable"|"disable"|"notify", optional_parameters (notify_user, open_url, open_pbk, data)}
       format.json  { render :json => response }
      end 
    else
      respond_to do |format|
       format.json  { render :json => {"error" => "fake_error"}, :status => 420 }
      end 
    end
  end

end